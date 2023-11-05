// AGoulder Copyright


#include "AbilitySystem/Data/AttributeInfo.h"


FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			UE_LOG(LogTemp, Warning, TEXT("Info.AttributeTag == Attribute Tag."));
			return Info;
		}
		//should match 1/x times where x = number of attributes
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for attribute tag [%s] on AttributeInfo [%s]."),*AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
