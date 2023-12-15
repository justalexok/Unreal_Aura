// AGoulder Copyright

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void OnRep_Stunned() override;

	//Combat Interface
	virtual int32 GetPlayerLevel_Implementation() override;

	//Player Interface
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() const override;
	virtual int32 FindPlayerLevelForXP_Implementation(int32 InXP) const override;
	virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;
	virtual int32 GetSpellPointsReward_Implementation(int32 Level) const override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	virtual int32 GetAttributePoints_Implementation() override;
	virtual int32 GetSpellPoints_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;
	
	virtual void SetInitAbilityActorInfo() override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpParticles() const;
	
};
