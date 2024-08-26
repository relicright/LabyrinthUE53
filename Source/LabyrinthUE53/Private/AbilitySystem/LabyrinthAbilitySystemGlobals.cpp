// Copyright Relic Rights Studio


#include "AbilitySystem/LabyrinthAbilitySystemGlobals.h"
#include "LabyrinthAbilityTypes.h"

FGameplayEffectContext* ULabyrinthAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FLabyrinthGameplayEffectContext;
}
