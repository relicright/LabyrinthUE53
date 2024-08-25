// Copyright Relic Rights Studio


#include "AbilitySystem/LabyrinthAbilitySystemGlobals.h"

FGameplayEffectContext* ULabyrinthAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return Super::AllocGameplayEffectContext();
	//return new FLabyrinthGameplayEffectContext;
}
