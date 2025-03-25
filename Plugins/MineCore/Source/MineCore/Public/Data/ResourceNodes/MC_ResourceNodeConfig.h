#pragma once

#include "CoreMinimal.h"
#include "Items/MC_Item.h"
#include "MC_LogChannels.h"
#include "MC_ResourceNodeConfig.generated.h"

//TODO: Create here a comment which describe what kind of the resource is for the given tier (ResourceNodeTier) : Tier1 - Stone etc.

/** Enum representing the different states of a resource node. */
UENUM(BlueprintType)
enum class EResourceNodeState : uint8
{
	STATE_1 UMETA(DisplayName = "State 1"), // No resources available
	STATE_2 UMETA(DisplayName = "State 2"),
	STATE_3 UMETA(DisplayName = "State 3"),
	STATE_4 UMETA(DisplayName = "State 4")
};

// Overloaded subtraction operator for EResourceNodeState
inline EResourceNodeState operator-(const EResourceNodeState NodeState, uint8 Number)
{
	// Cast the enum to uint8 to perform arithmetic operations
	uint8 NewValue = static_cast<uint8>(NodeState);

	// Check if subtraction would cause an underflow (result below 0)
	if (NewValue < Number) 
	{
		// Log a warning about underflow
		UE_LOGFMT(LogResourceNode, Warning, "Underflow detected in EResourceNodeState subtraction! NodeState: {0}, Number: {1}", NewValue, Number);
        
		// Return a fallback value (e.g., the first enum state)
		return EResourceNodeState::STATE_1; 
	}

	// Return the new enum value after subtraction
	return static_cast<EResourceNodeState>(NewValue - Number);
}

// Overloaded addition operator for EResourceNodeState
inline EResourceNodeState operator+(const EResourceNodeState NodeState, uint8 Number)
{
	// Cast the enum to uint8 to perform arithmetic operations
	uint8 NewValue = static_cast<uint8>(NodeState);

	// Check if the addition would exceed the maximum valid value for EResourceNodeState
	if (NewValue + Number > static_cast<uint8>(EResourceNodeState::STATE_4))
	{
		// Log a warning about overflow
		UE_LOGFMT(LogResourceNode, Warning, "Overflow detected in EResourceNodeState addition! NodeState: {0}, Number: {1}", NewValue, Number);
        
		// Return a fallback value (e.g., the maximum enum state)
		return EResourceNodeState::STATE_4; 
	}

	// Return the new enum value after addition
	return static_cast<EResourceNodeState>(NewValue + Number);
}

/** Base class for defining the parameters of a resource node. Contains configuration data related to resource nodes. */
UCLASS()
class MINECORE_API UMC_ResourceNodeConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("ResourceNodeConfig", GetFName()); }

	// A TMap that associates each resource node state (EResourceNodeState) with a static mesh (UStaticMesh*).  
	// Used to dynamically assign the appropriate static mesh based on the resource node's current state.  
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node | Config")
	TMap<EResourceNodeState, UStaticMesh*> ResourceNodeMaterials;
	
	//Tier of the resource node
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node | Config")
	EItemTier ResourceNodeTier;
	
	// Time interval (in seconds) to increase the state by 1.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node | Config")
	float TimeToIncreaseState = 5.0f;

	// Time required to mine 1 resource from the node
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource Node | Config")
	float MiningTime = 5.0f;
};
