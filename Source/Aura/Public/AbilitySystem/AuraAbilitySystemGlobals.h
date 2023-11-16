// AGoulder Copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "EngineUtils.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
