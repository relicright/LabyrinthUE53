// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LabyrinthBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "LabyrinthGameplayTags.h"
#include "AbilitySystem/LabyrinthAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "LabyrinthUE53/LabyrinthUE53.h"

ALabyrinthBaseCharacter::ALabyrinthBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	const FLabyrinthGameplayTags& GameplayTags = FLabyrinthGameplayTags::Get();

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
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

void ALabyrinthBaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ALabyrinthBaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultPrimarySkillAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondarySkillAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ALabyrinthBaseCharacter::AddCharacterAbilities()
{
	ULabyrinthAbilitySystemComponent* LabyrinthASC = CastChecked<ULabyrinthAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	LabyrinthASC->AddCharacterAbilities(StartupAbilities);
	LabyrinthASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}

void ALabyrinthBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

UAbilitySystemComponent* ALabyrinthBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* ALabyrinthBaseCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

FVector ALabyrinthBaseCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FLabyrinthGameplayTags& GameplayTags = FLabyrinthGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	// if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Tail))
	// {
	// 	return GetMesh()->GetSocketLocation(TailSocketName);
	// }
	return FVector();
}

AActor* ALabyrinthBaseCharacter::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> ALabyrinthBaseCharacter::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

FTaggedMontage ALabyrinthBaseCharacter::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
		{
			return TaggedMontage;
		}
	}
	return FTaggedMontage();
}

ECharacterClass ALabyrinthBaseCharacter::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

USkeletalMeshComponent* ALabyrinthBaseCharacter::GetWeapon_Implementation()
{
	return Weapon;
}

