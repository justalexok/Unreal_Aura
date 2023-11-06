// AGoulder Copyright


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Input Action that matches tag [%s] on InputConfig [%s]."),*InputTag.ToString(), *GetNameSafe(this)); //GetNameSafe is the name of the input config
		
	}
	return nullptr;
}
