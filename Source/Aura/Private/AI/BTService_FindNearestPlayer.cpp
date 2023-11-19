// AGoulder Copyright


#include "AI/BTService_FindNearestPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* OwningPawn = AIOwner->GetPawn();

	//TargetTag will be set to enemy if the owner of this service is the player
	//Usually owner will be enemy and target will be player
	const FName TargetTag =  OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> OutActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, OutActorsWithTag);

	//Find closest actor

	float ClosestDistance = TNumericLimits<float>::Max(); // Start with maximum a float can be
	AActor* ClosestActor = nullptr;
	for (AActor* Actor : OutActorsWithTag)
	{
		GEngine->AddOnScreenDebugMessage(1,1,FColor::Orange,*Actor->GetName());

		if (IsValid(Actor) && IsValid(OwningPawn))
		{
			const float Distance = OwningPawn->GetDistanceTo(Actor);
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = Actor;
			}
		}
		
	}
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowSelector, ClosestActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector, ClosestDistance);

}
