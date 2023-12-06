// AGoulder Copyright

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "SpellMenuWidgetController.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpellGlobeSelectedSignature, bool, bEquippedButtonEnabled, bool, bSpendPointButtonEnabled);

struct FAuraAbilityInfo;

struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category="Gas|Messages")
	FOnPlayerStateChangedSignature OnSpellPointsChanged;

	UPROPERTY(BlueprintAssignable, Category="Gas|SpellMenu")
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary/SpellMenu")
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

	static void ShouldEnableButtons(const FGameplayTag& StatusTag, int32 SpellPoints,  bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton);

private:
	FSelectedAbility SelectedAbility = { FAuraGameplayTags::Get().Abilities_Type_None, FAuraGameplayTags::Get().Abilities_Status_Locked};
	int32 CurrentSpellPoints = 0;
};
