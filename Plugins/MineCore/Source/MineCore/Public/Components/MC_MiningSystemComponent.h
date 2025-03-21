#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MC_MiningSystemComponent.generated.h"


UCLASS( ClassGroup=(MiningSystem), meta=(BlueprintSpawnableComponent) )
class MINECORE_API UMC_MiningSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//Constructor
	UMC_MiningSystemComponent();
};
