// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "LabyrinthPlayerController.generated.h"

class ALabyrinthCharacter;
struct FInputActionValue;
class IHighlightInterface;
class UInputMappingContext;
class UInputAction;
class ULabyrinthInputConfig;
class ULabyrinthAbilitySystemComponent;
class USplineComponent;

class UGameplayEffect;

enum class ETargetingStatus : uint8
{
	TargetingEnemy,
	TargetingNonEnemy,
	NotTargeting
};

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ALabyrinthPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ALabyrinthPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& InputActionValue);

private:
	
	UPROPERTY(EditAnywhere, Category="Pawn")
	TObjectPtr<ALabyrinthCharacter> ControlledPawn;

	FRotator CharacterRotation;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ShiftAction;

	void ShiftPressed() { bShiftKeyDown = true; };
	void ShiftReleased() { bShiftKeyDown = false; };
	bool bShiftKeyDown = false;
	
	void CursorTrace();
	TObjectPtr<AActor> LastActor;
	TObjectPtr<AActor> ThisActor;
	FHitResult CursorHit;
	static void HighlightActor(AActor* InActor);
	static void UnHighlightActor(AActor* InActor);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<ULabyrinthInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<ULabyrinthAbilitySystemComponent> LabyrinthAbilitySystemComponent;

	ULabyrinthAbilitySystemComponent* GetASC();
	
	void AutoRun();
	void FaceMouseCursor();

	bool bShouldFaceMouseCursor = true;

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	ETargetingStatus TargetingStatus = ETargetingStatus::NotTargeting;
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
};
