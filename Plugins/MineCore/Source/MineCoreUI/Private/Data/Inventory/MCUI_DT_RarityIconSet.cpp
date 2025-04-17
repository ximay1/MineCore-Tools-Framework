#include "Data/Inventory/MCUI_DT_RarityIconSet.h"
#include "MCUI_LogChannels.h"
#include "Data/Items/MC_DT_ItemConfig.h"

const TSoftObjectPtr<UTexture2D>& UMCUI_DT_RarityIconSet::GetIcon(EItemRarity Rarity) const
{
	switch (Rarity)
	{
		case EItemRarity::Common :
		{
			return CommonIcon;
		}
		case EItemRarity::Uncommon :
		{
			return UncommonIcon;
		}

		case EItemRarity::Rare :
		{
			return RareIcon;
		}
		
		case EItemRarity::Epic :
		{
			return EpicIcon;
		}

		case EItemRarity::Legendary :
		{
			return LegendaryIcon;
		}

		case EItemRarity::Mythic :
		{
			return MythicIcon;
		}
		default:
		{
			return CommonIcon;
		}
	}
}
