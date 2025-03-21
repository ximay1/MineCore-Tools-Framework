#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MC_InventoryComponent.generated.h"

UCLASS( ClassGroup=(MiningSystem), meta=(BlueprintSpawnableComponent) )
class MINECORE_API UMC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMC_InventoryComponent();

	/** Creates the inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void CreateInventory();

protected:
	// TODO: Change UUserWidget class to the base inventory widget class
	/** Widget class representing the Inventory */ 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Component")
	TSubclassOf<UUserWidget> InventoryClass;

	/** Map of items in the inventory. uint8 represents the number of slots. */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Component")
	TMap<uint8, UObject*> Items;
};