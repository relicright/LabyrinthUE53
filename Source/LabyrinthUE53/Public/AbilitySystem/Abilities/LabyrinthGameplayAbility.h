// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LabyrinthGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ULabyrinthGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	virtual FString GetDescription(int32 Level);
	virtual FString GetNextLevelDescription(int32 Level);
	static FString GetLockedDescription(int32 Level);

protected:

	float GetManaCost(float InLevel = 1.f) const;
	float GetCooldown(float InLevel = 1.f) const;
};
