#include "DeveloperSettings/MC_DeveloperSettings.h"

UMC_DeveloperSettings::UMC_DeveloperSettings()
{
	//Set values
	CategoryName = "Project";
	SectionName = "Mine Core";
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
