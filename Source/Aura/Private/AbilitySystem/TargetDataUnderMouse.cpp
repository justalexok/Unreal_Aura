// AGoulder Copyright


#include "AbilitySystem/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();

	if (PlayerController)
	{
		FHitResult CursorHit;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

		ValidData.Broadcast(CursorHit.Location);
	}
	}
	
