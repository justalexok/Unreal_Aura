// AGoulder Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton containing native gameplay tags
 */
struct FAuraGameplayTags
{
public:
      static const FAuraGameplayTags& Get() {return GameplayTags;}
      static void InitializeNativeGameplayTags();

 //Primary
      FGameplayTag Attributes_Primary_Strength;
      FGameplayTag Attributes_Primary_Intelligence;
      FGameplayTag Attributes_Primary_Resilience;
      FGameplayTag Attributes_Primary_Vigor;

//Secondary
      FGameplayTag Attributes_Secondary_Armor;
      FGameplayTag Attributes_Secondary_ArmorPenetration;
      FGameplayTag Attributes_Secondary_BlockChance;
      FGameplayTag Attributes_Secondary_CriticalHitChance;
      FGameplayTag Attributes_Secondary_CriticalHitDamage;
      FGameplayTag Attributes_Secondary_CriticalHitResistance;
      FGameplayTag Attributes_Secondary_HealthRegeneration;
      FGameplayTag Attributes_Secondary_ManaRegeneration;
      FGameplayTag Attributes_Secondary_MaxHealth;
      FGameplayTag Attributes_Secondary_MaxMana;

//Input
     FGameplayTag InputTag_LMB;
     FGameplayTag InputTag_RMB;
     FGameplayTag InputTag_1;
	 FGameplayTag InputTag_2;
     FGameplayTag InputTag_3;
     FGameplayTag InputTag_4;

//Resistances
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;

//Meta
	FGameplayTag Attributes_Meta_IncomingXP;

//DamageTypes
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

//Abilities
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;
	FGameplayTag Abilities_Fire_Firebolt;

//Cooldown
	FGameplayTag Cooldown_Fire_Firebolt;

//Sockets
	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Tail;

//MontageTags
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

//
	FGameplayTag Effects_HitReact;
private:
 static FAuraGameplayTags GameplayTags;
};
