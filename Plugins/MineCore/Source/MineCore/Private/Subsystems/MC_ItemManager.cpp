#include "Subsystems/MC_ItemManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Data/Items/MC_DT_ItemConfig.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MC_LogChannels.h"

void UMC_ItemManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    //LoadAllItemsFromFolder()
}

void UMC_ItemManager::LoadAllItemsFromFolder(const FString& PathFolder, const FPrimaryAssetType& PrimaryAssetType)
{
    // Execute only on the server
    if (UKismetSystemLibrary::IsServer(GetWorld()))
    {
        // Get the Asset Registry module
        FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");

        // Configure asset search parameters
        FARFilter Filter;
        Filter.PackagePaths.Add(*PathFolder);     // Target directory path
        Filter.bRecursivePaths = true;            // Search subdirectories recursively
        Filter.ClassPaths.Add(UMC_DT_ItemConfig::StaticClass()->GetClassPathName());  // Filter by specific asset class

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
                        UE_LOGFMT(LogItem, Warning, "Failed to cast asset %s to UMC_DT_ItemConfig", AssetId.ToString());
                    }
                }
            }));
    }
}