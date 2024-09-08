// Copyright Relic Rights Studio


#include "Player/LabyrinthPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/LabyrinthAbilitySystemComponent.h"
#include "AbilitySystem/LabyrinthAttributeSet.h"
#include "Net/UnrealNetwork.h"

ALabyrinthPlayerState::ALabyrinthPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<ULabyrinthAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<ULabyrinthAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

void ALabyrinthPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALabyrinthPlayerState, XP);
	DOREPLIFETIME(ALabyrinthPlayerState, Level);
	DOREPLIFETIME(ALabyrinthPlayerState, AttributePoints);
	DOREPLIFETIME(ALabyrinthPlayerState, SpellPoints);
}

UAbilitySystemComponent* ALabyrinthPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALabyrinthPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	UE_LOG(LogTemp, Warning, TEXT("XP GAIN: PLAYER STATE: %d"), InXP);
	UE_LOG(LogTemp, Warning, TEXT("Total XP GAIN: PLAYER STATE: %d"), XP);
	OnXPChangedDelegate.Broadcast(XP);
}

void ALabyrinthPlayerState::AddXPToAttribute(FGameplayTag Tag, int32 InXP)
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerState: AddXP to att: %s:%d"), *Tag.ToString(), InXP);
	
	if (AttributeXP.Contains(Tag))
	{
		AttributeXP[Tag] += InXP;
	}
	else
	{
		AttributeXP.Emplace(Tag, InXP);
	}

	// Check if the current XP is enough to level the skill up
	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);

		// If so set all of the XP for this attribute to 0
	
	OnXPToAttributeChangedDelegate.Broadcast(InXP);
}

void ALabyrinthPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level, true);
}

void ALabyrinthPlayerState::AddToAttributePoints(int32 InPoints)
{
	AttributePoints += InPoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void ALabyrinthPlayerState::AddToSpellPoints(int32 InPoints)
{
	SpellPoints += InPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void ALabyrinthPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void ALabyrinthPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level, false);
}

void ALabyrinthPlayerState::SetAttributePoints(int32 InPoints)
{
	AttributePoints = InPoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void ALabyrinthPlayerState::SetSpellPoints(int32 InPoints)
{
	SpellPoints = InPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void ALabyrinthPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level, true);
}

void ALabyrinthPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

void ALabyrinthPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void ALabyrinthPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}
