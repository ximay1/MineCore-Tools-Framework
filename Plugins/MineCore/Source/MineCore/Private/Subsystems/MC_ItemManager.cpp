#include "Subsystems/MC_ItemManager.h"
#include "MC_LogChannels.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Data/Items/MC_DT_ItemConfig.h"
#include "DeveloperSettings/MC_DeveloperSettings.h"
#include "Engine/AssetManager.h"
#include "Engine/AssetManagerSettings.h"
#include "Kismet/KismetSystemLibrary.h"

void UMC_ItemManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    // Execute only on the server
    if (UKismetSystemLibrary::IsServer(GetWorld()))
    {
        //Get Default UMC_DeveloperSettings
        const UMC_DeveloperSettings* MineCore_DeveloperSettings = GetDefault<UMC_DeveloperSettings>();
    
        //Get PrimaryAssetType
        FPrimaryAssetType PrimaryAssetType = MineCore_DeveloperSettings->PrimaryAssetType;

        //If PrimaryAssetType isn't valid, assign default value "ItemConfig"
        if (!PrimaryAssetType.IsValid())
        {
            PrimaryAssetType = "ItemConfig";
        }
        
        //Load Items from folders
        Server_LoadAllItemsFromFolders(PrimaryAssetType);
    }
}

int32 UMC_ItemManager::Server_CalculateTotalPower(TArray<int32>& OutIndividualPowers) const
{
    int32 TotalPower = 0;

    // Pre-allocate memory to prevent multiple reallocations
    OutIndividualPowers.Reserve(ItemDataStorage.Num());
    
    // Aggregate power values and populate output array
    for (const auto& [ItemId, ItemConfig] : ItemDataStorage)
    {
        const int32 ItemPower = ItemConfig->PowerStats.Power;
        OutIndividualPowers.Add(ItemPower);
        TotalPower += ItemPower;
    }
    
    return TotalPower;
}

void UMC_ItemManager::Server_GenerateWeightedRandomItems(const int32 NumItemsToGenerate, TArray<UMC_DT_ItemConfig*>& OutSelectedItems) const
{
    // Initialize containers
    TArray<int32> PowerWeights;
    TArray<UMC_DT_ItemConfig*> AllItemConfigs;
    
    // Extract all configs from map
    ItemDataStorage.GenerateValueArray(AllItemConfigs);
    
    // Calculate total weight (power) and get individual weights
    const int32 TotalWeight = Server_CalculateTotalPower(PowerWeights);

    // Guard against invalid input
    if(TotalWeight <= 0 || AllItemConfigs.IsEmpty()) 
    {
        UE_LOGFMT(LogItem, Warning, "Invalid items for weighted selection");
        return;
    }

    // Perform weighted random selection
    for(int32 SelectionCount = 0; SelectionCount < NumItemsToGenerate; SelectionCount++)
    {
        // Generate random threshold [1, TotalWeight]
        const int32 RandomWeightThreshold = FMath::RandRange(1, TotalWeight);
        
        // Find item crossing the weight threshold
        int32 CumulativeWeight = 0;
        for(int32 ItemIndex = 0; ItemIndex < PowerWeights.Num(); ItemIndex++)
        {
            CumulativeWeight += PowerWeights[ItemIndex];
            
            if(CumulativeWeight >= RandomWeightThreshold)
            {
                OutSelectedItems.Add(AllItemConfigs[ItemIndex]);
                break;
            }
        }
    }
}

void UMC_ItemManager::GenerateItemIdentifier(const FString& ItemName, EItemTier Tier, EItemRarity Rarity, FString& OutName) const
{
    OutName = FString::Printf(TEXT("%s_%d_%d"), *ItemName, static_cast<uint8>(Tier), static_cast<uint8>(Rarity));
}

void UMC_ItemManager::Server_LoadAllItemsFromFolders(const FPrimaryAssetType& PrimaryAssetType)
{
    // Get the Asset Registry module
    const FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");

    //Get Asset Manager Settings
    const UAssetManagerSettings* AssetManagerSettings = GetDefault<UAssetManagerSettings>();
    
    // Attempt to locate the asset type configuration from project settings
    // This verifies the type was properly registered in Asset Manager
    const FPrimaryAssetTypeInfo* PrimaryAssetTypeInfo = AssetManagerSettings->PrimaryAssetTypesToScan.FindByPredicate(
        [&PrimaryAssetType](const FPrimaryAssetTypeInfo& TypeInfo)
        {
            return TypeInfo.PrimaryAssetType == PrimaryAssetType;
        });

    // Safety check - this should never happen if types are properly configured
    // but protects against crashes if project setup is incomplete
    if (!PrimaryAssetTypeInfo)
    {
        // Log warning 
        UE_LOGFMT(LogItem, Warning, "Missing PrimaryAssetType configuration for: {0}", PrimaryAssetType.ToString());
    }
    
    // Configure asset search parameters
    FARFilter Filter;
    Filter.bRecursivePaths = true;                                                         // Search subdirectories recursively
    Filter.ClassPaths.Add(UMC_DT_ItemConfig::StaticClass()->GetClassPathName());      // Filter by specific asset class
    Filter.bRecursiveClasses = true;                                                       // Include all child classes
    Algo::Transform(PrimaryAssetTypeInfo->GetDirectories(), Filter.PackagePaths,  // Target directory paths
        [](const FDirectoryPath& Str) { return FName(*Str.Path); });

    // Find all assets matching the filter criteria
    TArray<FAssetData> FoundAssetData;
    AssetRegistryModule.Get().GetAssets(Filter, FoundAssetData);

    //Checks if the FoundAssetData is greater than 0
    if (FoundAssetData.Num() > 0)
    {
        // Prepare list of asset IDs for asynchronous loading
        TArray<FPrimaryAssetId> AssetIdsToLoad;
        AssetIdsToLoad.Reserve(FoundAssetData.Num());

        // Collect valid primary asset IDs
        for (const FAssetData& AssetData : FoundAssetData)
        {
            if (AssetData.IsValid())
            {
                AssetIdsToLoad.Add(AssetData.GetPrimaryAssetId());
            }
        }

        // Start asynchronous loading of assets
        UAssetManager::Get().LoadPrimaryAssets(AssetIdsToLoad, {}, FStreamableDelegate::CreateLambda([this, PrimaryAssetType]()
            {
                // Process loaded assets after async load completes
                TArray<UObject*> LoadedObjects;
                UAssetManager::Get().GetPrimaryAssetObjectList(PrimaryAssetType, LoadedObjects);

                // Populate the item database
                for (UObject* LoadedObject : LoadedObjects)
                {
                    if (UMC_DT_ItemConfig* ItemConfig = Cast<UMC_DT_ItemConfig>(LoadedObject))
                    {
                        //Build FName
                        FString KeyName;
                        GenerateItemIdentifier(ItemConfig->ItemName.ToString(), ItemConfig->ItemTier, ItemConfig->ItemRarity, KeyName);

                        //Add item
                        ItemDataStorage.Add(KeyName, ItemConfig);
                    }
                    else
                    {
                        // Log warning
                        UE_LOGFMT(LogItem, Warning, "Failed to cast asset {0} to UMC_DT_ItemConfig", LoadedObject->GetPrimaryAssetId().ToString());
                    }
                }
            }));
    }
    else
    {
        UE_LOGFMT(LogItem, Warning, "No valid assets found in the configured directories");
    }
}
