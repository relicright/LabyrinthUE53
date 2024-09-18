// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LabyrinthBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "LabyrinthGameplayTags.h"
#include "AbilitySystem/LabyrinthAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LabyrinthUE53/LabyrinthUE53.h"
#include "Net/UnrealNetwork.h"

ALabyrinthBaseCharacter::ALabyrinthBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	const FLabyrinthGameplayTags& GameplayTags = FLabyrinthGameplayTags::Get();

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Helmet = CreateDefaultSubobject<USkeletalMeshComponent>("Helmet");
	Helmet->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	Helmet->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Helmet->SetLeaderPoseComponent(GetMesh());

	Gloves = CreateDefaultSubobject<USkeletalMeshComponent>("Gloves");
	Gloves->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	Gloves->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Gloves->SetLeaderPoseComponent(GetMesh());

	Pants = CreateDefaultSubobject<USkeletalMeshComponent>("Pants");
	Pants->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	Pants->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Pants->SetLeaderPoseComponent(GetMesh());

	Chest = CreateDefaultSubobject<USkeletalMeshComponent>("Chest");
	Chest->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	Chest->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Chest->SetLeaderPoseComponent(GetMesh());

	Boots = CreateDefaultSubobject<USkeletalMeshComponent>("Boots");
	Boots->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	Boots->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Boots->SetLeaderPoseComponent(GetMesh());
	
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

void ALabyrinthBaseCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsStunned = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bIsStunned ? 0.f : BaseWalkSpeed;
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
	DOREPLIFETIME(ALabyrinthBaseCharacter, bIsStunned);
	DOREPLIFETIME(ALabyrinthBaseCharacter, bIsBurned);
	DOREPLIFETIME(ALabyrinthBaseCharacter, bIsBeingShocked);
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
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Body))
	{
		return GetMesh()->GetSocketLocation(BodySocketName);
	}
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

void ALabyrinthBaseCharacter::Die(const FVector& DeathImpulse)
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath(DeathImpulse);
}

void ALabyrinthBaseCharacter::MulticastHandleDeath_Implementation(const FVector& DeathImpulse)
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Weapon->AddImpulse(DeathImpulse * 0.1f, NAME_None, true);
	
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetMesh()->AddImpulse(DeathImpulse, NAME_None, true);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Dissolve();
	bDead = true;
	//BurnDebuffComponent->Deactivate();
	//StunDebuffComponent->Deactivate();
	OnDeathDelegate.Broadcast(this);
}

FOnDeathSignature& ALabyrinthBaseCharacter::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

FOnDamageSignature& ALabyrinthBaseCharacter::GetOnDamageSignature()
{
	return OnDamageDelegate;
}

ECharacterClass ALabyrinthBaseCharacter::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

USkeletalMeshComponent* ALabyrinthBaseCharacter::GetWeapon_Implementation()
{
	return Weapon;
}

void ALabyrinthBaseCharacter::OnRep_Stunned()
{
}

void ALabyrinthBaseCharacter::OnRep_Burned()
{
}

int32 ALabyrinthBaseCharacter::GetMinionCount_Implementation()
{
	return MinionCount;
}

bool ALabyrinthBaseCharacter::IsDead_Implementation() const
{
	return bDead;
}

UNiagaraSystem* ALabyrinthBaseCharacter::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

void ALabyrinthBaseCharacter::IncremenetMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

FOnASCRegistered& ALabyrinthBaseCharacter::GetOnASCRegisteredDelegate()
{
	return OnAscRegistered;
}

void ALabyrinthBaseCharacter::SetIsBeingShocked_Implementation(bool bInShock)
{
	bIsBeingShocked = bInShock;
}

bool ALabyrinthBaseCharacter::IsBeingShocked_Implementation() const
{
	return bIsBeingShocked;
}

