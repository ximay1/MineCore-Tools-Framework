#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MCUI_DT_RarityIconSet.generated.h"

enum class EItemRarity : uint8;

UCLASS()
class MINECOREUI_API UMCUI_DT_RarityIconSet : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Common rarity icon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity Icons")
	TSoftObjectPtr<UTexture2D> CommonIcon;

	/** Uncommon rarity icon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity Icons")
	TSoftObjectPtr<UTexture2D> UncommonIcon;

	/** Rare rarity icon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity Icons")
	TSoftObjectPtr<UTexture2D> RareIcon;

	/** Epic rarity icon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity Icons")
	TSoftObjectPtr<UTexture2D> EpicIcon;

	/** Legendary rarity icon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity Icons")
	TSoftObjectPtr<UTexture2D> LegendaryIcon;

	/** Mythic rarity icon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity Icons")
	TSoftObjectPtr<UTexture2D> MythicIcon;

	/** Returns the texture icon associated with the specified item rarity */
	const TSoftObjectPtr<UTexture2D>& GetIcon(EItemRarity Rarity) const;
};
