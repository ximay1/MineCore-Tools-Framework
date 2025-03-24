#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MC_PlayerCharacter.generated.h"

UCLASS()
class MINECORE_API AMC_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Constructor */
	AMC_PlayerCharacter();
	
	/** Events */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
