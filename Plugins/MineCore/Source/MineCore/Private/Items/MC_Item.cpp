#include "Items/MC_Item.h"

#include "Net/UnrealNetwork.h"

void UMC_Item::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UMC_Item, ItemConfig, COND_OwnerOnly);
}
