#include "Subsystems/MC_ItemManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Data/Items/MC_DT_ItemConfig.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MC_LogChannels.h"
#include "DeveloperSettings/MC_DeveloperSettings.h"
#include "Engine/AssetManagerSettings.h"

void UMC_ItemManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    //Load Items from folders
    LoadAllItemsFromFolders(GetDefault<UMC_DeveloperSettings>()->PrimaryAssetType);
}

void UMC_ItemManager::LoadAllItemsFromFolders(const FPrimaryAssetType& PrimaryAssetType)
{
    // Execute only on the server
    if (UKismetSystemLibrary::IsServer(GetWorld()))
    {
        // Get the Asset Registry module
        FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");

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
        Algo::Transform(PrimaryAssetTypeInfo->GetDirectories(), Filter.PackagePaths,  // Target directory paths
            [](const FDirectoryPath& Str) { return FName(*Str.Path); });

        // Find all assets matching the filter criteria
        TArray<FAssetData> FoundAssetData;
        AssetRegistryModule.Get().GetAssets(Filter, FoundAssetData);

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
                    //Get Primary Asset ID
                    const FPrimaryAssetId AssetId = LoadedObject->GetPrimaryAssetId();
                    
                    if (UMC_DT_ItemConfig* ItemConfig = Cast<UMC_DT_ItemConfig>(LoadedObject))
                    {
                        ItemDataStorage.Add(AssetId, ItemConfig);
                    }
                    else
                    {
                        // Log warning
                        UE_LOGFMT(LogItem, Warning, "Failed to cast asset {0} to UMC_DT_ItemConfig", AssetId.ToString());
                    }
                }
            }));
    }
}