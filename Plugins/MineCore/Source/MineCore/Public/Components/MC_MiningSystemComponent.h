#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MC_MiningSystemComponent.generated.h"

class UMC_Pickaxe;

UCLASS( ClassGroup=(MiningSystem), meta=(BlueprintSpawnableComponent) )
class MINECORE_API UMC_MiningSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//Constructor
	UMC_MiningSystemComponent();

protected:
	/** Cached pickaxe (the best pickaxe in the inventory). It can be nullptr when player doesn't have any pickaxe in the inventory */
	TWeakObjectPtr<UMC_Pickaxe> CachedPickaxe;
};
