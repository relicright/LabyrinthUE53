// Copyright Relic Rights Studio


#include "Character/LabyrinthCharacter.h"

#include "AbilitySystemComponent.h"
#include "LabyrinthGameplayTags.h"
#include "AbilitySystem/LabyrinthAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/LabyrinthPlayerState.h"
#include "LabyrinthUE53/Public/Interaction/CombatInterface.h"
#include "Player/LabyrinthPlayerController.h"

ALabyrinthCharacter::ALabyrinthCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ALabyrinthCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();

	//TODO: Re-enable after saving and loading is figured out
	// LoadProgress();
	//
	// if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	// {
	// 	AuraGameMode->LoadWorldState(GetWorld());
	// }
}

void ALabyrinthCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void ALabyrinthCharacter::InitAbilityActorInfo()
{
	
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	LabyrinthPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(LabyrinthPlayerState, this);
	Cast<ULabyrinthAbilitySystemComponent>(LabyrinthPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = LabyrinthPlayerState->GetAbilitySystemComponent();
	AttributeSet = LabyrinthPlayerState->GetAttributeSet();
	OnAscRegistered.Broadcast(AbilitySystemComponent);
	//AbilitySystemComponent->RegisterGameplayTagEvent(FLabyrinthGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ALabyrinthCharacter::StunTagChanged);

	if (ALabyrinthPlayerController* AuraPlayerController = Cast<ALabyrinthPlayerController>(GetController()))
	{
		// if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		// {
		// 	AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		// }
	}
}
