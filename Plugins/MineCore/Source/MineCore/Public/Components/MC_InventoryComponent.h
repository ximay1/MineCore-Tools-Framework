#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/MC_Item.h"
#include "MineCore/Public/Data/Items/MC_ItemConfig.h"
#include "MC_InventoryComponent.generated.h"

class UMC_Item;

#pragma region UE_EDITOR_MACROS

#if WITH_EDITOR
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

/** Triggered when an item is added (Slot number, Item). */  
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAddedToInventory, uint8, Slot, UMC_Item*, Item);

/** Base class for the inventory system used in MineCore. */
UCLASS( ClassGroup=(MiningSystem), meta=(BlueprintSpawnableComponent) )
class MINECORE_API UMC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	// TODO: Change UUserWidget class to the base InventoryWidget class
	
public:	
	// Sets default values for this component's properties
	UMC_InventoryComponent();
	
	/** Creates the inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void CreateInventory();

	/** Refresh Widget Inventory */
	void RefreshInventoryWidget();
	
	/** Adds an item to the specified inventory slot */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Inventory Component")
	void AddItemToSlot(uint8 Slot, UMC_Item* Item);

	/** Adds an item to the first available slot in the inventory */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Inventory Component")
	void AddItemToFirstAvailableSlot(UMC_Item* Item);

	/** Removes an item from the inventory */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Inventory Component")
	void RemoveItemFromInventory(uint8 Slot, EItemAction ItemAction);

	/** Get Items */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void GetItems(TArray<UMC_Item*>& OutItems) const { Items.GenerateValueArray(OutItems); }
	
	/** Checks if an item exists in the inventory. Returns UMC_Item if found, otherwise nullptr */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	FORCEINLINE UMC_Item* GetItemFromInventory(uint8 Slot) const { return Items.FindRef(Slot); }

	/** Finds items in the inventory based on the given filter criteria. */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void FindItemsByFilter(const FInventoryItemFilter& InventoryItemFilter, TArray<UMC_Item*>& OutItems) const;
	
	/** This function attempts to find the best item in the Inventory. */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	UMC_Item* FindBestItemInInventory(const TSubclassOf<UMC_Item>& ItemClass) const;
	
	/** Drops the item from the specified inventory slot as a bag at the player's location */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void DropItemBySlot(uint8 Slot);

	/** Drops the specified item as a bag at the player's location */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	void DropItemInstance(UMC_Item* Item);
	
	/** Finds the first available (empty) slot in the inventory. Returns true if a valid slot is found, otherwise false. */
	UFUNCTION(BlueprintCallable, Category = "Inventory Component")
	bool FindValidSlot(uint8& OutSlot) const;
	
	/** Get Max Slots */
	UFUNCTION(BlueprintGetter, Category = "Inventory Component")
	FORCEINLINE uint8 GetMaxSlots() const { return MaxSlots; }

public:
	//Delegates
	FOnItemAddedToInventory OnItemAddedToInventory;
	
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
	
	/** Maximum number of slots in the inventory */
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Component", meta = (AllowPrivateAccess))
	uint8 MaxSlots;
};