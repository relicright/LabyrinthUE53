// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LabyrinthBaseCharacter.h"

#include "LabyrinthGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "LabyrinthUE53/LabyrinthUE53.h"

ALabyrinthBaseCharacter::ALabyrinthBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	const FLabyrinthGameplayTags& GameplayTags = FLabyrinthGameplayTags::Get();
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void ALabyrinthBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALabyrinthBaseCharacter::InitAbilityActorInfo()
{
}

void ALabyrinthBaseCharacter::Tick(float DeltaTime)
{
}

void ALabyrinthBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//TODO: Add in all of the rep lifetime defaults every character will have.
}

float ALabyrinthBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnDamageDelegate.Broadcast(DamageTaken);
	return DamageTaken;
}

void ALabyrinthBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ALabyrinthBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

