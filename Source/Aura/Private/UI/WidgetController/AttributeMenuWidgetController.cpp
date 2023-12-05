// AGoulder Copyright


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
	check(AttributeInfo);

	//Loop through the TagsToAttributes Map - Adding lambda to each delegate, that will broadcast the updated info
	for (auto& Pair : GetAuraAS()->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
[this, Pair](const FOnAttributeChangeData& Data)
		{
		BroadcastInfo(Pair.Key, Pair.Value());
		}
	);
	}

	
	GetAuraPS()->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 Points)
		{
			AttributePointsChangedDelegate.Broadcast(Points);
		});
	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);

	//TagsToAttribute is a Key/Value map of GameplayTags and Function Pointers
	for (const auto& Pair : GetAuraAS()->TagsToAttributes)
	{
		BroadcastInfo(Pair.Key, Pair.Value());
	}
	AttributePointsChangedDelegate.Broadcast(GetAuraPS()->GetAttributePoints());
	
}


void UAttributeMenuWidgetController::BroadcastInfo(const FGameplayTag Tag, const FGameplayAttribute& Attribute) const
{
	//Gets the Info for Tag, sets the new value to Info.AttributeValue, Broadcasts the Info.
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Tag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpgradeAttribute(AttributeTag);
}

