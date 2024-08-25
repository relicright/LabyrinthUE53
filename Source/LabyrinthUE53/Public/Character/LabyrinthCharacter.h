// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "Character/LabyrinthBaseCharacter.h"
#include "Interaction/PlayerInterface.h"
#include "LabyrinthCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	virtual void InitAbilityActorInfo() override;
};
