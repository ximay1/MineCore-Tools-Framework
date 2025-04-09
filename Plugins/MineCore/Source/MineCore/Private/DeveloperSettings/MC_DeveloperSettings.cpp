#include "DeveloperSettings/MC_DeveloperSettings.h"

UMC_DeveloperSettings::UMC_DeveloperSettings()
{
	//Set values
	CategoryName = "Project";
	SectionName = "Mine Core";
}

FName UMC_DeveloperSettings::GetCategoryName() const
{
	return FName("Project");
}

#if WITH_EDITOR
FText UMC_DeveloperSettings::GetSectionText() const
{
	return NSLOCTEXT("MineCoreSettings", "MineCoreSettingsSection", "Mine Core");
}

FText UMC_DeveloperSettings::GetSectionDescription() const
{
	return NSLOCTEXT("MineCoreSettings", "MineCoreSettingsDescription", "Mine Core Settings");
}
#endif
