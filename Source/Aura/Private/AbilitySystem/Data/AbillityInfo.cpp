// AGoulder Copyright


#include "AbilitySystem/Data/AbillityInfo.h"

#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbillityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound)
{
	for (const FAuraAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;			
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find info for ability tag %s on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	return FAuraAbilityInfo();
}