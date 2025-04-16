#include "MineCore/Public/Data/Items/MC_DT_ItemConfig.h"
#include "Items/MC_Item.h"

void UMC_DT_ItemConfig::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//Recalculate the power
	RecalculatePower();
}

int32 UMC_DT_ItemConfig::RecalculatePower()
{
	return PowerStats.Power = PowerStats.BasePower + (static_cast<uint8>(ItemRarity) + 1) * (static_cast<uint8>(ItemTier) + 1);
}

void UMC_DT_ItemConfig::GetStatsProperties(TMap<FString, FString>& OutProperties)
{
	OutProperties.Add(TEXT("Something"), FString::Printf(TEXT("%f"), Weight));
}

