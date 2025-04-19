#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MC_HUD.generated.h"

class UMC_ItemContextMenu;
class UMC_Game_Layout;

UCLASS()
class MINECORE_API AMC_HUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Constructor */
	AMC_HUD();
	
	/** Get GameLayout */
	UFUNCTION(BlueprintGetter, Category = "HUD")
	UMC_Game_Layout* GetGameLayout() const { return GameLayout; }
	
protected:
	/** Events */
	virtual void BeginPlay() override;

	/** MCUI_Game_Layout Widget Object */
	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	TObjectPtr<UMC_Game_Layout> GameLayout;
	
	/** MCUI_Game_Layout Widget Class */
	UPROPERTY(EditDefaultsOnly, Category = "HUD", meta = (AllowedClasses = "MCUI_Game_Layout"))
	TSubclassOf<UUserWidget> GameLayout_Class;

	/** MCUI_ItemContextMenu Class */
	UPROPERTY(BlueprintReadWrite, Category = "HUD")
	TObjectPtr<UMC_ItemContextMenu> ItemContextMenu;
	
	/** MCUI_ItemContextMenu Class */
	UPROPERTY(EditDefaultsOnly, Category = "HUD", meta = (AllowedClasses = "MCUI_ItemContextMenu"))
	TSubclassOf<UUserWidget> ItemContextMenu_Class;
};
