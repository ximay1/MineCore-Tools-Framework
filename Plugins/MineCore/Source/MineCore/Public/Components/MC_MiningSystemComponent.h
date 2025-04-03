#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MC_MiningSystemComponent.generated.h"

/** Forward Declarations */
class UMC_Pickaxe;
class UMC_InventoryComponent;

/** Base class for the MiningSystemComponent used in MineCore. Handles mining-related functionality and interactions. */
UCLASS( ClassGroup=(MineCore), meta=(BlueprintSpawnableComponent) )
class MINECORE_API UMC_MiningSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Constructor */
	UMC_MiningSystemComponent();

	/** Events */
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** initialize the Mining System Component. Should be always called on the client-side */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	virtual void InitializeMiningSystemComponent();
	
	/** This function checks if the player is able to mine the resource node. Always called on the server! */
	bool CanPlayerMine(UMC_MiningTool* MiningTool);

	/** Caches mining tools from the player's inventory */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	void CacheMiningToolsFromInventory();

	/** Get Mining Tool */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	FORCEINLINE UMC_MiningTool* GetMiningTool(TSubclassOf<UMC_MiningTool> Class) { return *CachedMiningTools.Find(Class); }
	
	template<typename MiningToolClass>
	FORCEINLINE MiningToolClass* GetMiningTool() { return Cast<MiningToolClass>(*CachedMiningTools.Find(MiningToolClass::StaticClass())); }
	
	/** Start Mining */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Mining System Component")
	virtual void StartMining(); 
	
	/** Stop Mining */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Mining System Component")
	virtual void StopMining(); 

	/** This function attempts to find the inventory component. */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	UMC_InventoryComponent* FindInventory() const;

protected:

	/** Initializes the Mining System Component on the server. */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Mining System Component")
	virtual void Server_InitializeMiningSystemComponent();
	
	/** Is Player Mining */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Mining System Component")
	bool IsPlayerMining;
	
	/** Cached pointers to mining tools in the inventory (key = tool class).
	 * Value can be nullptr if the player doesn't have any mining tool of the given class.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Mining System Component")
	TMap<TSubclassOf<UMC_MiningTool>, UMC_MiningTool*> CachedMiningTools;
	
	/** Cached pointer to the inventory component. It should never be nullptr. */
	UPROPERTY(BlueprintReadOnly, Category = "Mining System Component")
	TObjectPtr<UMC_InventoryComponent> InventoryComponent;
};