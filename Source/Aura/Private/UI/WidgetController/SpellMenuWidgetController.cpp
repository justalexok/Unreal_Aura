// AGoulder Copyright


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbillityInfo.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraASC()->AbilityStatusChanged.AddLambda(
		[this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag)
	{
		if (AbilityInfo)
		{
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});

	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda([this](int32 SpellPoints)
	{
		OnSpellPointsChanged.Broadcast(SpellPoints);
	});

	
	
}

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	OnSpellPointsChanged.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	bool bEquipButtonEnabled = false;
	bool bSpendPointButtonEnabled = false;

	//Get Status Tag for AbilityTag
	const FGameplayAbilitySpec* Spec = GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);
	if (Spec == nullptr) 
	{
		SpellGlobeSelectedDelegate.Broadcast(bEquipButtonEnabled, bSpendPointButtonEnabled);
		return;
	}
	const FGameplayTag StatusTag = GetAuraASC()->GetStatusFromSpec(*Spec);
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Equipped) || StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bEquipButtonEnabled = true;
		bSpendPointButtonEnabled = true;
	}
	else if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		bEquipButtonEnabled = false;
		bSpendPointButtonEnabled = true;
	}
	if (GetAuraPS()->GetSpellPoints() == 0)
	{
		bSpendPointButtonEnabled = false;
	}
	//if Locked then both remain disabled
	SpellGlobeSelectedDelegate.Broadcast(bEquipButtonEnabled, bSpendPointButtonEnabled);
}


