// Copyright Relic Rights Studio


#include "Player/LabyrinthPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/LabyrinthAbilitySystemComponent.h"
#include "AbilitySystem/LabyrinthAbilitySystemLibrary.h"
#include "AbilitySystem/LabyrinthAttributeSet.h"
#include "AbilitySystem/Data/ItemInfo.h"
#include "AbilitySystem/Data/AttributeXPLevelInfo.h"
#include "Interaction/PlayerInterface.h"
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
	DOREPLIFETIME(ALabyrinthPlayerState, LastSkillUsed);
}

UAbilitySystemComponent* ALabyrinthPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALabyrinthPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
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
	const UAttributeXPLevelInfo* AttributeLevelInfo = ULabyrinthAbilitySystemLibrary::GetAttributeSkillXPInfo(GetAbilitySystemComponent()->GetAvatarActor());
	const FRealCurve* LevelUpCurve = AttributeLevelInfo->AttributeSkillXPRequirements->FindCurve(*Tag.ToString(), FString());
	const float CurrentXP = AttributeXP[Tag];
	UE_LOG(LogTemp, Warning, TEXT("PlayerState: CurrentXP: %f"), CurrentXP);

	ULabyrinthAttributeSet* LabyrinthAttSet = Cast<ULabyrinthAttributeSet>(AttributeSet);
	TStaticFuncPtr<FGameplayAttribute()> InAttribute = LabyrinthAttSet->TagsToAttributes[Tag];
	const float CurrentSkill = InAttribute().GetNumericValue(LabyrinthAttSet);
	UE_LOG(LogTemp, Warning, TEXT("PlayerState: CurrentSkill: %f"), CurrentSkill);
	
	const float LevelUpCoefficient = LevelUpCurve->Eval(CurrentSkill);
	UE_LOG(LogTemp, Warning, TEXT("PlayerState: LevelUpCoefficient: %f"), LevelUpCoefficient);

	// If so set all of the XP for this attribute to 0
	if (CurrentXP > LevelUpCoefficient)
	{
		AttributeXP[Tag] = 0;
		if (CurrentSkill < 100)
		{
			GetAbilitySystemComponent()->SetNumericAttributeBase(InAttribute(), CurrentSkill + 1);
		}
	}
	
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

void ALabyrinthPlayerState::SetLastUsedSkill(FGameplayTag LastUsedSkillTag)
{
	LastSkillUsed = LastUsedSkillTag;
}

void ALabyrinthPlayerState::ApplyEquipmentArmorEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass, const FGameplayTag& SlotTag, const FItemDefaultInfo& ArmorInfo, int32 ItemLevel)
{
	check(AbilitySystemComponent);
	check(GameplayEffectClass);

	bool bRemovedArmor = false;
	for (auto ArmorEffectHandle : ActiveArmorEffectHandles)
	{
		if (ArmorEffectHandle.Value == SlotTag)
		{
			bRemovedArmor = true;
		}
	}

	if (bRemovedArmor)
	{
		RemoveEquipmentArmorEffectAndApplyNew(SlotTag, GameplayEffectClass, SlotTag, ArmorInfo, ItemLevel);
	}
	else
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
			GameplayEffectClass,
			ItemLevel,
			EffectContextHandle
			);
		const FActiveGameplayEffectHandle ActiveEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		ActiveArmorEffectHandles.Add(ActiveEffectHandle, SlotTag);
	}
}

void ALabyrinthPlayerState::RemoveEquipmentArmorEffect(FGameplayTag Tag)
{
	TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	for (TTuple<FActiveGameplayEffectHandle, FGameplayTag> HandlePair : ActiveArmorEffectHandles)
	{
		if (Tag == HandlePair.Value)
		{
			AbilitySystemComponent->RemoveActiveGameplayEffect(HandlePair.Key, 1);
			HandlesToRemove.Add(HandlePair.Key);
		}
	}
	for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
	{
		ActiveArmorEffectHandles.FindAndRemoveChecked(Handle);
	}
}

void ALabyrinthPlayerState::RemoveEquipmentArmorEffectAndApplyNew(FGameplayTag Tag,
	TSubclassOf<UGameplayEffect> GameplayEffectClass, const FGameplayTag& SlotTag,
	const FItemDefaultInfo& ArmorInfo, int32 ItemLevel)
{
	TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	for (TTuple<FActiveGameplayEffectHandle, FGameplayTag> HandlePair : ActiveArmorEffectHandles)
	{
		if (Tag == HandlePair.Value)
		{
			AbilitySystemComponent->RemoveActiveGameplayEffect(HandlePair.Key, 1);
			HandlesToRemove.Add(HandlePair.Key);
		}
	}
	for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
	{
		ActiveArmorEffectHandles.FindAndRemoveChecked(Handle);
	}

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		GameplayEffectClass,
		ItemLevel,
		EffectContextHandle
		);
	const FActiveGameplayEffectHandle ActiveEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	ActiveArmorEffectHandles.Add(ActiveEffectHandle, SlotTag);
}

void ALabyrinthPlayerState::RemoveEquipmentArmorVisual(FGameplayTag SlotTag)
{
	check(AbilitySystemComponent);


}

void ALabyrinthPlayerState::AddEquipmentArmorVisual(FGameplayTag SlotTag, const FItemDefaultInfo& ArmorInfo)
{
	
}

void ALabyrinthPlayerState::OnRep_LastSkillUsed(FGameplayTag OldLastSkillUsed)
{
	
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
