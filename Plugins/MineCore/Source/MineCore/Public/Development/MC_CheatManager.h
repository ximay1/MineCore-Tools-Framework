#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "MC_LogChannels.h"
#include "Items/MC_Item.h"
#include "MC_CheatManager.generated.h"

UCLASS()
class MINECORE_API UMC_CheatManager : public UCheatManager
{
	GENERATED_BODY()

public:

	
	
protected:
	/**
	 * Searches for a class by name from the given input string and returns a pointer to the UClass if found.
	 * The expected input format is: "StaticClass=ClassName"
	 * 
	 * Example usage:
	 *     UClass* MyClass = FindAndPrintClass("StaticClass=MyCustomClass");
	 * 
	 * If the class is found, it logs: "Class Name: MyCustomClass" and returns the class pointer.
	 * If not found, it logs a warning and returns nullptr.
	*/
	UClass* FindAndPrintClass(FString InputString);
};
