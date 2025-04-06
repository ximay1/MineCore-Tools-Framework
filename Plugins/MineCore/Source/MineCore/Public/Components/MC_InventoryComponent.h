#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MC_InventoryComponent.generated.h"

/** Forward Declarations */
class UMC_Item;
class UMC_DT_ItemConfig;
class UMC_DT_DefaultInventoryData;
enum class EItemTier : uint8;
enum class EItemCategory : uint8;
enum class EItemRarity : uint8;

#pragma region UE_EDITOR_MACROS

#if !UE_BUILD_SHIPPING
	// Macro to log error if the slot number is invalid, but doesn't return anything
	#define VALIDATE_SLOT(Slot, MaxSlots) \
		if (Slot > MaxSlots) \
		{ \
			UE_LOGFMT(LogInventory, Error, "Invalid slot number. Slot exceeds MaxSlots. File - {0}, Line - {1}.", __FILE__, __LINE__); \
		}

	// Macro to log error if the item is invalid (nullptr), but doesn't return anything
	#define VALIDATE_ITEM(Item) \
		if (Item == nullptr) \
		{ \
			UE_LOGFMT(LogInventory, Error, "Item is nullptr. File - {0}, Line - {1}.", __FILE__, __LINE__); \
		}


	// Macro to check if the slot number is valid, returns false if invalid
	#define VALIDATE_SLOT_AND_RETURN(Slot, MaxSlots, bIsValid) \
		if (Slot > MaxSlots) \
		{ \
			UE_LOGFMT(LogInventory, Error, "Invalid slot number. Slot exceeds MaxSlots. File - {0}, Line - {1}.", __FILE__, __LINE__); \
			bIsValid = false; \
		}

	// Macro to check if the item is valid (not nullptr), returns false if invalid
	#define VALIDATE_ITEM_AND_RETURN(Item, bIsValid) \
		if (Item == nullptr) \
		{ \
			UE_LOGFMT(LogInventory, Error, "Item is nullptr. File - {0}, Line - {1}.", __FILE__, __LINE__); \
			bIsValid = false; \
		}

	// Macro to validate both slot and item without returning
	#define VALIDATE_ITEM_AND_SLOT(Slot, MaxSlots, Item) \
		VALIDATE_SLOT(Slot, MaxSlots) \
		VALIDATE_ITEM(Item)

	// Macro to validate both slot and item, returns false if either is invalid
	#define VALIDATE_ITEM_AND_SLOT_RETURN(Slot, MaxSlots, Item, bIsValid) \
		VALIDATE_SLOT_AND_RETURN(Slot, MaxSlots, bIsValid) \
		VALIDATE_ITEM_AND_RETURN(Item, bIsValid)
#endif

#pragma endregion

/** 
 * This struct defines the filter criteria for searching items in the inventory.
 */
USTRUCT(BlueprintType)
struct FInventoryItemFilter
{
	GENERATED_BODY()

	/** Constructors */
	FInventoryItemFilter();
	FInventoryItemFilter(TSubclassOf<UMC_Item> InItemClass, EItemTier InMinTier, EItemTier InMaxTier, EItemCategory InItemCategory, EItemRarity InItemRarity);

#pragma region INCLUSION_FILTERS
	/** The class type of the item to search for */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Filter")
	TSubclassOf<UMC_Item> ItemClass;

	/** The minimum tier required for the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Filter")
	EItemTier MinTier;

	/** The maximum tier allowed for the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Filter")
	EItemTier MaxTier;

	/** The category of the item (e.g., Weapon, Armor, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Filter")
	EItemCategory ItemCategory;

	/** The rarity of the item (e.g., Common, Rare, Epic) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Filter")
	EItemRarity ItemRarity;
#pragma endregion

#pragma region FILTER_FLAGS
	
	/** Flag indicating whether to filter by item class */
	bool bUseItemClass = false;
	
	/** Flag indicating whether to filter by minimum tier */
	bool bUseMinTier = false;
	
	/** Flag indicating whether to filter by maximum tier */
	bool bUseMaxTier = false;
	
	/** Flag indicating whether to apply the category filter */
	bool bUseCategoryFilter = false;
	
	/** Flag indicating whether to apply the rarity filter */
	bool bUseRarityFilter = false;
	
#pragma endregion
};

/** Enum representing possible actions that can be performed on an item. */
UENUM(BlueprintType)
enum class EItemAction : uint8
{
	Destroy UMETA(DisplayName = "Destroy"),  // Player wants to destroy the item
	Drop    UMETA(DisplayName = "Drop"),     // Player wants to drop the item
};

/** 
 * The struct can be used for mapping items to specific inventory slots, 
 * making it easy to manage and replicate inventory data in multiplayer scenarios.
 */
USTRUCT(BlueprintType)
struct FInventoryItemsMap  
{
	GENERATED_BODY()
	
	/** Slot in the inventory that holds the item */
	UPROPERTY()
	uint8 Slot = {};

	/** Pointer to the item in the given slot */
	UPROPERTY()
	TObjectPtr<UMC_Item> Item;

	bool operator==(const FInventoryItemsMap& Other) const
	{
		return this->Slot == Other.Slot;
	}
};

/** Defines a complete in-game item instance */ 
USTRUCT(BlueprintType)
struct FItemDefinition
{
	GENERATED_BODY()

public:

	/** Constructors */
	FItemDefinition() = default;
	FItemDefinition(UMC_DT_ItemConfig* NewItemConfig);
	
	//Item Data Config
	UPROPERTY(BlueprintReadWrite, Category = "Inventory Component | Item Definition")
	TObjectPtr<UMC_DT_ItemConfig> ItemConfig;

	bool operator==(const FItemDefinition& Other) const
	{
		return ItemConfig == Other.ItemConfig;
	}
};

/** Base class for the inventory system used in MineCore. */
UCLASS(ClassGroup=(MineCore), meta=(BlueprintSpawnableComponent))
class MINECORE_API UMC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	// TODO: Change UUserWidget class to the base InventoryWidget class
	
public:	
	/** Constructor */
	UMC_InventoryComponent();

	/** Events */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Creates the inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	virtual void Client_CreateInventory();

	/** Refresh Widget Inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	virtual void Client_RefreshInventoryWidget();

	/** Get Max Slots */
	UFUNCTION(BlueprintGetter, Category = "Inventory Component")
	FORCEINLINE uint8 GetMaxSlots() const { return MaxSlots; }

	/** Finds the first available (empty) slot in the inventory. Returns true if a valid slot is found, otherwise false. */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	bool FindValidSlot(uint8& OutSlot) const;

	/** Adds an item to the specified inventory slot */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory Component")
	virtual void Server_AddItemToSlot(uint8 Slot, const FItemDefinition& ItemDefinition);

	/** Adds an item to the first available slot in the inventory */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory Component")
	virtual void Server_AddItemToFirstAvailableSlot(const FItemDefinition& ItemDefinition);

	/** Removes an item from the inventory */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory Component")
	virtual void Server_RemoveItemFromInventory(uint8 Slot, EItemAction ItemAction);

	/** Get all items in the inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void GetInventoryItems(TArray<UMC_Item*>& OutItems) const { Items.GenerateValueArray(OutItems); }

	/** Get all items in the inventory as a map */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void GetInventoryItemsMap(TMap<uint8, UMC_Item*>& OutItems) const { OutItems = Items; }

	/** Checks if an item exists in the inventory. Returns UMC_Item if found, otherwise nullptr */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	FORCEINLINE UMC_Item* GetItemFromInventory(uint8 Slot) const { return Items.FindRef(Slot); }

	/** Finds items in the inventory based on the given filter criteria. */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	virtual void FindItemsByFilter(const FInventoryItemFilter& InventoryItemFilter, TArray<UMC_Item*>& OutItems) const;

	/** This function attempts to find the best item in the Inventory. */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	UMC_Item* FindBestItemInInventory(const TSubclassOf<UMC_Item>& ItemClass) const;

	/** Drops the item from the specified inventory slot as a bag at the player's location */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	virtual void Server_DropItemBySlot(uint8 Slot);

	/** Drops the specified item as a bag at the player's location */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	virtual void Server_DropItemInstance(UMC_Item* Item);
	
	/** Initializes the inventory system by loading default items and setting up initial state. */	
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory Component")
	virtual void Server_InitializeInventory();

	/** Creates item instance from definition data */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	virtual UMC_Item* Server_ConstructItem(const FItemDefinition& ItemDefinition);

	/** Destroys item instance */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory Component")
	virtual void Server_DestroyItem(const FInventoryItemsMap& ItemToDestroy);

	/** Get Items_Array C++ */
	FORCEINLINE const TArray<FInventoryItemsMap>& GetItemsArray() const { return Items_Array; }

	/** Get Items_Array BP */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	FORCEINLINE void BP_GetItemsArray(TArray<FInventoryItemsMap>& OutResult) const { OutResult = GetItemsArray(); }
	
protected:
	/** Widget class representing the Inventory */ 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Component")
	TSubclassOf<UUserWidget> InventoryClass;

	/** Cached Pointer to the Inventory widget */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Component")
	TObjectPtr<UUserWidget> InventoryWidget;

	/** Map of items in the inventory. uint8 represents a number of slot. */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Component")
	TMap<uint8, UMC_Item*> Items;

	/** Array of items in the inventory. Each entry contains a slot and the corresponding item stored in that slot. */
	UPROPERTY(ReplicatedUsing = OnRep_Items_Array)
	TArray<FInventoryItemsMap> Items_Array;

	/** Called when the Items_Array is replicated to the owner. */
	UFUNCTION()
	void OnRep_Items_Array();

#if WITH_EDITORONLY_DATA
	
	/** This data asset contains default inventory, it will be applied on the begin play */
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Component")
	TObjectPtr<UMC_DT_DefaultInventoryData> DefaultInventory;
	
#endif
	
	/** Maximum number of slots in the inventory */
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Component", meta = (AllowPrivateAccess))
	uint8 MaxSlots;
};