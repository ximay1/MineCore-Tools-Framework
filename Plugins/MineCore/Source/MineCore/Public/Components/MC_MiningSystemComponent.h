#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MC_MiningSystemComponent.generated.h"

/** Forward Declarations */
class UMC_Pickaxe;
class UMC_Axe;
class UMC_Hammer;
class UMC_Knife;
class UMC_Sickle;
class UMC_InventoryComponent;
class UMC_MiningTool;

/** This struct contains the cached mining tools */
USTRUCT(BlueprintType)
struct FCachedMiningTools
{
	GENERATED_BODY()

	/** Cached Pickaxe */
	UPROPERTY(BlueprintReadOnly, Category = "Cached Mining Tools")
	TObjectPtr<UMC_Pickaxe> CachedPickaxe;

	/** Cached Axe */
	UPROPERTY(BlueprintReadOnly, Category = "Cached Mining Tools")
	TObjectPtr<UMC_Axe> CachedAxe;

	/** Cached Hammer */
	UPROPERTY(BlueprintReadOnly, Category = "Cached Mining Tools")
	TObjectPtr<UMC_Hammer> CachedHammer;

	/** Cached Knife */
	UPROPERTY(BlueprintReadOnly, Category = "Cached Mining Tools")
	TObjectPtr<UMC_Knife> CachedKnife;

	/** Cached Sickle */
	UPROPERTY(BlueprintReadOnly, Category = "Cached Mining Tools")
	TObjectPtr<UMC_Sickle> CachedSickle;
};

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

	/** Get Pickaxe */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	FORCEINLINE UMC_Pickaxe* GetPickaxe() const { return CachedMiningTools.CachedPickaxe; }

	/** Get Axe */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	FORCEINLINE UMC_Axe* GetAxe() const { return CachedMiningTools.CachedAxe; }

	/** Get Hammer */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	FORCEINLINE UMC_Hammer* GetHammer() const { return CachedMiningTools.CachedHammer; }

	/** Get Knife */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	FORCEINLINE UMC_Knife* GetKnife() const { return CachedMiningTools.CachedKnife; }

	/** Get Sickle */
	UFUNCTION(BlueprintCallable, Category = "Mining System Component")
	FORCEINLINE UMC_Sickle* GetSickle() const { return CachedMiningTools.CachedSickle; }
	
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
	
	/** Cached pointers to mining tools in the inventory. */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Mining System Component")
	FCachedMiningTools CachedMiningTools;
	
	/** Cached pointer to the inventory component. It should never be nullptr. */
	UPROPERTY(BlueprintReadOnly, Category = "Mining System Component")
	TObjectPtr<UMC_InventoryComponent> InventoryComponent;
};