// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "Character/LabyrinthBaseCharacter.h"
#include "Interaction/PlayerInterface.h"
#include "LabyrinthCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
struct FGameplayAttribute;

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ALabyrinthCharacter : public ALabyrinthBaseCharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	ALabyrinthCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Player Interface */
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() const override;
	virtual void AddXPToAttribute_Implementation(FGameplayTag Tag, int32 InXP) const override;
	virtual FGameplayTag GetLastSkillUsed_Implementation() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetLastSkillUsed_Implementation(FGameplayTag LastUsedSkillTag) override;
	
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
	virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;
	virtual int32 GetSpellPointsReward_Implementation(int32 Level) const override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	virtual int32 GetAttributePoints_Implementation() const override;
	virtual int32 GetSpellPoints_Implementation() const override;
	/** end Player Interface */
	
	/** Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	/** end Combat Interface */
	
	UPROPERTY(EditDefaultsOnly)
	float DeathTime = 5.f;

	FTimerHandle DeathTimer;

	void SetCharacterPawnRotation(FRotator NewRotation);
	
	UFUNCTION(Server, Reliable)
	void ServerSetCharacterPawnRotation(FRotator NewRotation);
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetCharacterPawnRotation(FRotator NewRotation);

	UFUNCTION(BlueprintCallable, Category="Character")
	void SetShouldFaceMouseCursor(bool bShouldFace);

protected:

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	virtual void InitAbilityActorInfo() override;

	bool bShouldFaceMouseCursor = true;

	UPROPERTY(EditDefaultsOnly, Category="Character", meta=(AllowPrivateAccess="true"))
	float CharacterRotationSpeed = .05f;
};
