// AGoulder Copyright


#include "AbilitySystem/Data/AttributeInfo.h"


FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for attribute tag [%s] on AttributeInfo [%s]."),*AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
