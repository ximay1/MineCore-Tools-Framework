#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MC_PlayerController.generated.h"

class AMC_HUD;

UCLASS()
class MINECORE_API AMC_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Get Mine Core HUD */
	UFUNCTION(BlueprintGetter, Category = "MC Player Controller")
	AMC_HUD* GetMCHUD();
};
