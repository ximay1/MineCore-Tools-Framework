#include "Items/MC_Item.h"
#include "Net/UnrealNetwork.h"

void UMC_Item::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UMC_Item, ItemConfig, COND_OwnerOnly);
}

int32 UMC_Item::Server_AddToStack(int32 Amount)
{
	// Validate input parameters
	if (Amount <= 0 || !IsStackable())
	{
		UE_LOGFMT(LogItem, Warning, "Invalid AddToStack request for {0}: Amount={1} (expected positive), Stackable={2}", GetName(), Amount, IsStackable());
		return 0;
	}

	// Cache old value for delta calculation
	const int32 OldValue = CurrentStackCount;
    
	// Apply with protection against overflow
	CurrentStackCount = FMath::Clamp(OldValue + Amount, 1, ItemConfig->MaxStackSize);
	
	// Return actual delta
	return CurrentStackCount - OldValue;
}

int32 UMC_Item::Server_RemoveFromStack(int32 Amount)
{
	// Validate input parameters
	if (Amount <= 0)
	{
		UE_LOGFMT(LogItem, Warning, "Invalid RemoveFromStack request for {0}: Amount={1} (expected positive)", GetName(), Amount);
		return 0;
	}

	// Cache old value for delta calculation
	const int32 OldValue = CurrentStackCount;
    
	// Apply with protection underflow (minimum 1 item)
	CurrentStackCount = FMath::Max(1, CurrentStackCount - Amount);
    
	// Return actual delta
	return OldValue - CurrentStackCount;
}
