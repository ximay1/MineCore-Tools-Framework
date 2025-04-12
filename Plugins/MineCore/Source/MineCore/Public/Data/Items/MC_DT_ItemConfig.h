#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MC_DT_ItemConfig.generated.h"

/** Forward Declarations */
class UMC_Item;

/** Enum representing the tier of an item or resource node. */
UENUM(BlueprintType)
enum class EItemTier : uint8
{
	Tier1	UMETA(DisplayName = "Tier 1"),
	Tier2	UMETA(DisplayName = "Tier 2"),
	Tier3	UMETA(DisplayName = "Tier 3"),
	Tier4	UMETA(DisplayName = "Tier 4"),
	Tier5	UMETA(DisplayName = "Tier 5"),
	Tier6	UMETA(DisplayName = "Tier 6"),
	Tier7	UMETA(DisplayName = "Tier 7"),
	Tier8	UMETA(DisplayName = "Tier 8"),
	Tier9	UMETA(DisplayName = "Tier 9"),
	Tier10	UMETA(DisplayName = "Tier 10")
};

/** Enum representing the rarity of an item */
UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common		UMETA(DisplayName = "Common"),
	Uncommon	UMETA(DisplayName = "Uncommon"),
	Rare		UMETA(DisplayName = "Rare"),
	Epic		UMETA(DisplayName = "Epic"),
	Legendary	UMETA(DisplayName = "Legendary"),
	Mythic		UMETA(DisplayName = "Mythic")
};

/** Item representing the category of an item */
UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Resource	UMETA(DisplayName = "Resource"),
	Tool		UMETA(DisplayName = "Tools"),         
};

/** Structure representing the power stats */
USTRUCT(BlueprintType)
struct FItemPowerStats
{
	GENERATED_BODY()

	/** Power of Item */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Item Power")
	int32 Power = {};
	
	/** Base Power of Item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Power", meta = (ClampMin = 0))
	int32 BasePower = {};
};

/** Base class for item configurations. Defines common properties for all items. */
UCLASS()
class MINECORE_API UMC_DT_ItemConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("ItemConfig", GetFName()); }
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
	/** Class of item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config")
	TSubclassOf<UMC_Item> ItemClass;

	/** Item tier */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config")
	EItemTier ItemTier = {};
	
	/** The category of the item (e.g., weapon, resource, armor, etc.) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config")
	EItemCategory ItemCategory = {};

	/** Rarity of the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config")
	EItemRarity ItemRarity = {};
	
	/** Power of the Item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config")
	FItemPowerStats PowerStats;
	
	/** Weight */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config")
	float Weight = 0.0f;

	/** MaxStackSize in the inventory. Max = 999 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config", meta = (InlineEditConditionToggle, ClampMin = 1, ClampMax = 999))
	int32 MaxStackSize = 1;

	/** Name of the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config", meta = (AssetBundles = "UI"))
	FText ItemName;

	/** A short description of the item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config", meta = (AssetBundles = "UI", MultiLine))
	FText ItemDescription;
	
	/** Icon representing the item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config", meta = (AssetBundles = "UI"))
	TSoftObjectPtr<UTexture2D> ItemIcon;

	/** Recalculate power */
	UFUNCTION(BlueprintCallable, Category = "Item Config")
	virtual int32 RecalculatePower();
};