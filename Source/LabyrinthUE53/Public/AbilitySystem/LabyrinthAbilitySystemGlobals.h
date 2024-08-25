// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "LabyrinthAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ULabyrinthAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
