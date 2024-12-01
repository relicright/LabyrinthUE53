// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LabyrinthDamageGameplayAbility.h"
#include "LabyrinthProjectileSpell.generated.h"

class ALabyrinthProjectile;

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ULabyrinthProjectileSpell : public ULabyrinthDamageGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch = false, float PitchOverride = 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ALabyrinthProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	int32 NumProjectiles = 5;
};
