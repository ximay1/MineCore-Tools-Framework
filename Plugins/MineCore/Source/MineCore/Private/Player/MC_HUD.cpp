#include "Player/MC_HUD.h"
#include "Blueprint/UserWidget.h"
#include "Layouts/MCUI_Game_Layout.h"

void AMC_HUD::BeginPlay()
{
	Super::BeginPlay();

	//Create W_Game_Layout widget
	GameLayout = CreateWidget<UMCUI_Game_Layout>(GetOwningPlayerController(), GameLayout_Class);

	//Add to viewport
	GameLayout->AddToViewport();
}
