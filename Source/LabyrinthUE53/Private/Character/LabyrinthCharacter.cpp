// Copyright Relic Rights Studio


#include "Character/LabyrinthCharacter.h"

#include "AbilitySystemComponent.h"
#include "LabyrinthGameplayTags.h"
#include "AbilitySystem/LabyrinthAbilitySystemComponent.h"
#include "AbilitySystem/LabyrinthAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Game/LabyrinthGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/LabyrinthPlayerState.h"
#include "Player/LabyrinthPlayerController.h"
#include "UI/HUD/LabyrinthHUD.h"
#include "LabyrinthUE53/Public/Interaction/CombatInterface.h"
#include "Net/UnrealNetwork.h"

ALabyrinthCharacter::ALabyrinthCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CharacterClass = ECharacterClass::WarTemplar;
}

void ALabyrinthCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
	InitializeDefaultAttributes();
	AddCharacterAbilities();

	// 
	// LoadProgress();
	//
	// if (ALabyrinthGameModeBase* LabyrinthGameMode = Cast<ALabyrinthGameModeBase>(UGameplayStatics::GetGameMode(this)))
	// {
	// 	LabyrinthGameMode->LoadWorldState(GetWorld());
	// }
}

void ALabyrinthCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void ALabyrinthCharacter::AddToXP_Implementation(int32 InXP)
{
	UE_LOG(LogTemp, Warning, TEXT("Incoming XP2 Character: %d"), InXP);
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	LabyrinthPlayerState->AddToXP(InXP);
}

void ALabyrinthCharacter::LevelUp_Implementation()
{
	
}

int32 ALabyrinthCharacter::GetXP_Implementation() const
{
	const ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	return LabyrinthPlayerState->GetXP();
}

void ALabyrinthCharacter::AddXPToAttribute_Implementation(FGameplayTag Tag, int32 InXP) const
{
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	LabyrinthPlayerState->AddXPToAttribute(Tag, InXP);
}

FGameplayTag ALabyrinthCharacter::GetLastSkillUsed_Implementation()
{
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	return LabyrinthPlayerState->GetLastSkillUsed();
}

void ALabyrinthCharacter::SetLastSkillUsed_Implementation(FGameplayTag LastUsedSkillTag)
{
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	return LabyrinthPlayerState->SetLastUsedSkill(LastUsedSkillTag);
}

int32 ALabyrinthCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	const ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	//return LabyrinthPlayerState->LevelUpInfo->FindLevelForXP(InXP);
	return 0; // Change this later
}

int32 ALabyrinthCharacter::GetAttributePointsReward_Implementation(int32 Level) const
{
	const ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	//return LabyrinthPlayerState->LevelUpInfo->LevelUpInformation[Level].AttributePointAward;
	return 0; // Change this later
}

int32 ALabyrinthCharacter::GetSpellPointsReward_Implementation(int32 Level) const
{
	const ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	//return LabyrinthPlayerState->LevelUpInfo->LevelUpInformation[Level].SpellPointAward;
	return 0; // Change this later
}

void ALabyrinthCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	LabyrinthPlayerState->AddToLevel(InPlayerLevel);

	if (ULabyrinthAbilitySystemComponent* LabyrinthASC = Cast<ULabyrinthAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		//LabyrinthASC->UpdateAbilityStatuses(LabyrinthPlayerState->GetPlayerLevel());
	}
}

void ALabyrinthCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	LabyrinthPlayerState->AddToAttributePoints(InAttributePoints);
}

void ALabyrinthCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	LabyrinthPlayerState->AddToSpellPoints(InSpellPoints);
}

int32 ALabyrinthCharacter::GetAttributePoints_Implementation() const
{
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	return LabyrinthPlayerState->GetAttributePoints();
}

int32 ALabyrinthCharacter::GetSpellPoints_Implementation() const
{
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	return LabyrinthPlayerState->GetSpellPoints();
}

void ALabyrinthCharacter::UpdateMovementSpeed_Implementation(int32 Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	ClientUpdateMovementSpeed(Speed);
}

void ALabyrinthCharacter::ClientUpdateMovementSpeed_Implementation(int32 Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

int32 ALabyrinthCharacter::GetPlayerLevel_Implementation()
{
	const ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	return LabyrinthPlayerState->GetPlayerLevel();
}

void ALabyrinthCharacter::Die(const FVector& DeathImpulse)
{
	Super::Die(DeathImpulse);

	FTimerDelegate DeathTimerDelegate;
	DeathTimerDelegate.BindLambda([this]()
	{
		ALabyrinthGameModeBase* LabyrinthGM = Cast<ALabyrinthGameModeBase>(UGameplayStatics::GetGameMode(this));
		if (LabyrinthGM)
		{
			LabyrinthGM->PlayerDied(this);
		}
	});
	GetWorldTimerManager().SetTimer(DeathTimer, DeathTimerDelegate, DeathTime, false);
	TopDownCameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

void ALabyrinthCharacter::SetCharacterPawnRotation(FRotator NewRotation)
{
	if (!bShouldFaceMouseCursor) return;
	SetActorRotation( FMath::Lerp(GetActorRotation(), NewRotation, CharacterRotationSpeed) );
	ServerSetCharacterPawnRotation(NewRotation);
}

void ALabyrinthCharacter::SetShouldFaceMouseCursor(bool bShouldFace)
{
	bShouldFaceMouseCursor = bShouldFace;
}

void ALabyrinthCharacter::EquipArmor_Implementation(const FGameplayTag& ArmorItem, FGameplayTag& ArmorSlotTag,
                                                    const int32 Level)
{
	// TODO:  Check the overlapping item either by mouse cursor or standing over to see which item should be sent to be equipped.
	// It might be possible to use Gameplay cue to equip armor, but if not then multicast should work for this.
	// Should also be useable from the inventory which means we cant use overlap here, we'd have to use that in the input somewhere
	// Error: Says something about ReceiveFastArrayItem: Invalid property terminator handle
	
	ServerEquipArmor(ArmorItem, ArmorSlotTag, Level);
}

void ALabyrinthCharacter::ServerEquipArmor_Implementation(const FGameplayTag& ArmorItem, const FGameplayTag& ArmorSlotTag,
                                                          const int32 Level)
{
	// TODO: Need to check if the player actually has the armor in their inventory to equip or if they are standing near the item
	
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);

	const ALabyrinthGameModeBase* LabyrinthGameMode = Cast<ALabyrinthGameModeBase>(UGameplayStatics::GetGameMode(this));
	check(LabyrinthGameMode)
	const FItemDefaultInfo ArmorInfo = LabyrinthGameMode->ArmorItemInfo->GetArmorItemInfo(ArmorItem);
	LabyrinthPlayerState->ApplyEquipmentArmorEffect(ArmorInfo.PrimaryGameplayEffect, ArmorInfo.EquipmentSlotTag, ArmorInfo, Level);

	MulticastEquipArmor(ArmorItem, ArmorSlotTag);
	// TODO: Should most likely send a multicast here to show the item equipped on the player to everyone
}

void ALabyrinthCharacter::UnEquipArmor_Implementation(FGameplayTag ArmorSlotTag)
{
	// TODO: Need to check if the player actually has the armor in their inventory eqipped to unequip
	
	ServerUnEquipArmor(ArmorSlotTag);
}

void ALabyrinthCharacter::ServerUnEquipArmor_Implementation(const FGameplayTag ArmorSlotTag)
{
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	LabyrinthPlayerState->RemoveEquipmentArmorEffect(ArmorSlotTag);

	MulticastUnEquipArmor(ArmorSlotTag);
	// TODO: Should most likely send a multicast here to remove the item equipped on the player to everyone
}

void ALabyrinthCharacter::MulticastEquipArmor_Implementation(const FGameplayTag& ArmorItem,
	const FGameplayTag& ArmorSlotTag)
{
	ALabyrinthPlayerState* LabyrinthPlayerState = GetPlayerState<ALabyrinthPlayerState>();
	check(LabyrinthPlayerState);
	const FItemDefaultInfo ArmorInfo = LabyrinthPlayerState->ArmorItemInfo->GetArmorItemInfo(ArmorItem);

	bool bFoundEquippedArmor = false;
	for (auto Pair : EquippedArmor)
	{
		if (Pair.Key == ArmorInfo.EquipmentSlotTag)
		{
			// Already has equipment
			bFoundEquippedArmor = true;
			UE_LOG(LogTemp, Warning, TEXT("Already has armor equipped in this slot"));
		}
	}

	if (!bFoundEquippedArmor)
	{
		EquippedArmor.Add(ArmorInfo.EquipmentSlotTag, ArmorInfo);
		UE_LOG(LogTemp, Warning, TEXT("armor equipped in this slot"));

		if (ArmorInfo.EquipmentSlotTag == FLabyrinthGameplayTags::Get().Equipment_Armor_Chest) Chest->SetSkeletalMesh(ArmorInfo.Mesh);
		else if (ArmorInfo.EquipmentSlotTag == FLabyrinthGameplayTags::Get().Equipment_Armor_Helmet) Helmet->SetSkeletalMesh(ArmorInfo.Mesh);
		else if (ArmorInfo.EquipmentSlotTag == FLabyrinthGameplayTags::Get().Equipment_Armor_Legs) Pants->SetSkeletalMesh(ArmorInfo.Mesh);
		else if (ArmorInfo.EquipmentSlotTag == FLabyrinthGameplayTags::Get().Equipment_Armor_Feet) Boots->SetSkeletalMesh(ArmorInfo.Mesh);
		else if (ArmorInfo.EquipmentSlotTag == FLabyrinthGameplayTags::Get().Equipment_Armor_Gloves) Gloves->SetSkeletalMesh(ArmorInfo.Mesh);
	}
}

void ALabyrinthCharacter::MulticastUnEquipArmor_Implementation(const FGameplayTag ArmorSlotTag)
{
	bool bFoundEquippedArmor = false;
	for (auto Pair : EquippedArmor)
	{
		if (Pair.Key == ArmorSlotTag)
		{
			// Already has equipment
			bFoundEquippedArmor = true;
			UE_LOG(LogTemp, Warning, TEXT("Already has armor equipped in this slot"));
		}
	}
	if (bFoundEquippedArmor)
	{
		EquippedArmor.Remove(ArmorSlotTag);
		if (ArmorSlotTag == FLabyrinthGameplayTags::Get().Equipment_Armor_Chest) Chest->SetSkeletalMesh(nullptr);
		else if (ArmorSlotTag == FLabyrinthGameplayTags::Get().Equipment_Armor_Helmet) Helmet->SetSkeletalMesh(nullptr);
		else if (ArmorSlotTag == FLabyrinthGameplayTags::Get().Equipment_Armor_Legs) Pants->SetSkeletalMesh(nullptr);
		else if (ArmorSlotTag == FLabyrinthGameplayTags::Get().Equipment_Armor_Feet) Boots->SetSkeletalMesh(nullptr);
		else if (ArmorSlotTag == FLabyrinthGameplayTags::Get().Equipment_Armor_Gloves) Gloves->SetSkeletalMesh(nullptr);
	}
}

void ALabyrinthCharacter::ServerSetCharacterPawnRotation_Implementation(FRotator NewRotation)
{
	MulticastSetCharacterPawnRotation(NewRotation);
}

void ALabyrinthCharacter::MulticastSetCharacterPawnRotation_Implementation(FRotator NewRotation)
{
	SetActorRotation( FMath::Lerp(GetActorRotation(), NewRotation, CharacterRotationSpeed) );
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
	AbilitySystemComponent->RegisterGameplayTagEvent(FLabyrinthGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ALabyrinthCharacter::StunTagChanged);

	if (ALabyrinthPlayerController* LabyrinthPlayerController = Cast<ALabyrinthPlayerController>(GetController()))
	{
		if (ALabyrinthHUD* LabyrinthHUD = Cast<ALabyrinthHUD>(LabyrinthPlayerController->GetHUD()))
		{
			LabyrinthHUD->InitOverlay(LabyrinthPlayerController, LabyrinthPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
