#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MC_ItemConfig.generated.h"

UENUM(BlueprintType)
enum class EItemTier : uint8
{
	IT_Tier1 UMETA(DisplayName = "Tier 1"),
	IT_Tier2 UMETA(DisplayName = "Tier 2"),
	IT_Tier3 UMETA(DisplayName = "Tier 3"),
	IT_Tier4 UMETA(DisplayName = "Tier 4"),
	IT_Tier5 UMETA(DisplayName = "Tier 5"),
	IT_Tier6 UMETA(DisplayName = "Tier 6"),
	IT_Tier7 UMETA(DisplayName = "Tier 7"),
	IT_Tier8 UMETA(DisplayName = "Tier 8"),
	IT_Tier9 UMETA(DisplayName = "Tier 9"),
	IT_Tier10 UMETA(DisplayName = "Tier 10"),
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	IR_Common		UMETA(DisplayName = "Common"),
	IR_Uncommon		UMETA(DisplayName = "Uncommon"),
	IR_Rare			UMETA(DisplayName = "Rare"),
	IR_Epic			UMETA(DisplayName = "Epic"),
	IR_Legendary	UMETA(DisplayName = "Legendary"),
	IR_Mythic		UMETA(DisplayName = "Mythic"),
};

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	IC_Resources	 UMETA(DisplayName = "Resources"),
	IC_Tools		 UMETA(DisplayName = "Tools"),         
};

UCLASS()
class MINECORE_API UMC_ItemConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/** Item tier */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config")
	EItemTier ItemTier;
	
	/** The category of the item (e.g., weapon, resource, armor, etc.) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config")
	EItemCategory ItemCategory;
	
	/** Does item supports ItemRarity */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config", meta = (InlineEditConditionToggle))
	bool SupportsItemRarity;
    
	/** Rarity of the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config", meta = (EditCondition = SupportsItemRarity))
	EItemRarity ItemRarity;

	/** Weight */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config")
	float Weight = 0.0f;

	/** MaxStackSize in the inventory. Max = 999 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config", meta = (InlineEditConditionToggle))
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
};