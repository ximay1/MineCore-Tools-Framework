#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_ResourceNodeSpawner.generated.h"

UCLASS()
class MINECORE_API AMC_ResourceNodeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Constructor */
	AMC_ResourceNodeSpawner();

protected:
	/** ~ Begin AActor Interface */
	virtual void BeginPlay() override;
	/** ~ End AActor Interface */
};
