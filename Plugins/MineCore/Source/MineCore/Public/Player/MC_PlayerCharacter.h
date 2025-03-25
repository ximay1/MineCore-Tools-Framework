#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MC_PlayerCharacter.generated.h"

class UMC_InventoryComponent;
class UMC_MiningSystemComponent;

/** Base class for characters used in MineCore. */
UCLASS()
class MINECORE_API AMC_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Constructor */
	AMC_PlayerCharacter();
	
	/** Events */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Get Inventory Component */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	FORCEINLINE UMC_InventoryComponent* GetInventoryComponent() const { return InventoryComponent; } 

	/** Get Mining System Component */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	FORCEINLINE UMC_MiningSystemComponent* GetMiningSystemComponent() const { return MiningSystemComponent; }
	
protected:
	/** Inventory Component */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Component")
	TObjectPtr<UMC_InventoryComponent> InventoryComponent;

	/** Mining System Component */
	UPROPERTY(BlueprintReadOnly, Category = "Mining System Component")
	TObjectPtr<UMC_MiningSystemComponent> MiningSystemComponent;
};
