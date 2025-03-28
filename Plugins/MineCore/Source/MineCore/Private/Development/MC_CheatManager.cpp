#include "Development/MC_CheatManager.h"

UClass* UMC_CheatManager::FindAndPrintClass(FString InputString)
{
	FString ClassName;
    
	// Extract the class name from the input string using the "StaticClass=" prefix
	if (FParse::Value(*InputString, TEXT("StaticClass="), ClassName))
	{
		// Try to find the class by its name in the engine's object registry
		if (UClass* FoundClass = FindFirstObject<UClass>(*ClassName))
		{
			UE_LOGFMT(LogTemp, Log, "Class Name: {0}", FoundClass->GetName());
			return FoundClass; // Return the found class
		}
		else
		{
			// Log a warning if the class was not found
			UE_LOGFMT(LogTemp, Warning, "Class not found: {0}", ClassName);
		}
	}
	else
	{
		// Log a warning if the input string does not contain "StaticClass="
		UE_LOGFMT(LogTemp, Warning, "Invalid input format. Expected format: StaticClass=ClassName");
	}

	// Return nullptr if class was not found or input was invalid
	return nullptr; 
}