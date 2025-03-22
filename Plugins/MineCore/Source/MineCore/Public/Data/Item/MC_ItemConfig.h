#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MC_ItemConfig.generated.h"

UENUM(BlueprintType)
enum class EItemTier : uint8
{
	Tier1 UMETA(DisplayName = "Tier 1"),
	Tier2 UMETA(DisplayName = "Tier 2"),
	Tier3 UMETA(DisplayName = "Tier 3"),
	Tier4 UMETA(DisplayName = "Tier 4"),
	Tier5 UMETA(DisplayName = "Tier 5"),
	Tier6 UMETA(DisplayName = "Tier 6"),
	Tier7 UMETA(DisplayName = "Tier 7"),
	Tier8 UMETA(DisplayName = "Tier 8"),
	Tier9 UMETA(DisplayName = "Tier 9"),
	Tier10 UMETA(DisplayName = "Tier 10"),
};

UCLASS()
class MINECORE_API UMC_ItemConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/** Item tier */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Config")
	EItemTier ItemTier;
};
