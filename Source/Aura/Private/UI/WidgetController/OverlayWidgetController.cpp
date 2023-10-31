// AGoulder Copyright


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());

}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// Binding HealthChanged function to the delegate that is broadcast when Health Attribute changes	
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
	// .AddUObject(this, &UOverlayWidgetController::HealthChanged);

	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
	// .AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
	// .AddUObject(this, &UOverlayWidgetController::ManaChanged);
	//
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
	// .AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	//Replacing Callbacks with Lambdas
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data){OnHealthChanged.Broadcast(Data.NewValue);	} );
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data) {OnMaxHealthChanged.Broadcast(Data.NewValue); } );
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data){OnManaChanged.Broadcast(Data.NewValue); } );
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data){OnMaxManaChanged.Broadcast(Data.NewValue);	} );
	

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			
			for (const FGameplayTag& Tag : AssetTags)
			{
				// E.g Tag = Message.HealthPotion returns true
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
				
				
			}
		}	
	);
}

// void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
// {
//
// 	OnHealthChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnMaxHealthChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnManaChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnMaxManaChanged.Broadcast(Data.NewValue);
// }
