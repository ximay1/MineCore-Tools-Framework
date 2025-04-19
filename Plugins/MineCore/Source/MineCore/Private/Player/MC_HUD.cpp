#include "Player/MC_HUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Layouts/MC_Game_Layout.h"

AMC_HUD::AMC_HUD()
{
	//Disable ticking
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AMC_HUD::BeginPlay()
{
	Super::BeginPlay();

	//Create W_Game_Layout widget
	GameLayout = CreateWidget<UMC_Game_Layout>(GetOwningPlayerController(), GameLayout_Class);

	//Add to viewport
	GameLayout->AddToViewport();
}
