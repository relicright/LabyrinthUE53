// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/LabyrinthAttributeSet.h"
#include "Game/LabyrinthGameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystem/Data/ItemInfo.h"
#include "LabyrinthPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class ULevelUpInfo;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelChanged, int32 /*StatValue*/, bool /*bLevelUp*/)

// typedef is specific to the FGameplayAttribute() signature, but TStaticFunPtr is generic to any signature chosen
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ALabyrinthPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALabyrinthPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnXPToAttributeChangedDelegate;
	FOnLevelChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;
	FOnPlayerStatChanged OnSpellPointsChangedDelegate;

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetXP() const { return XP; }
	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
	FORCEINLINE int32 GetSpellPoints() const { return SpellPoints; }
	FORCEINLINE FGameplayTag GetLastSkillUsed() const { return LastSkillUsed; }

	void AddToXP(int32 InXP);
	void AddXPToAttribute(FGameplayTag Tag, int32 InXP);
	void AddToLevel(int32 InLevel);
	void AddToAttributePoints(int32 InPoints);
	void AddToSpellPoints(int32 InPoints);
	
	void SetXP(int32 InXP);
	void SetLevel(int32 InLevel);
	void SetAttributePoints(int32 InPoints);
	void SetSpellPoints(int32 InPoints);
	void SetLastUsedSkill(FGameplayTag LastUsedSkillTag);
	
	void ApplyEquipmentArmorEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass, const FGameplayTag& SlotTag, const FItemDefaultInfo& ArmorInfo,  int32 ItemLevel);
	void RemoveEquipmentArmorEffect(FGameplayTag Tag);
	void RemoveEquipmentArmorEffectAndApplyNew(FGameplayTag Tag, TSubclassOf<UGameplayEffect> GameplayEffectClass, const FGameplayTag& SlotTag, const FItemDefaultInfo& ArmorInfo,  int32 ItemLevel);

protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY()
	TObjectPtr<ALabyrinthGameModeBase> GameMode;

	UPROPERTY()
	TMap<FGameplayTag, int32> AttributeXP;

	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, FGameplayTag> ActiveArmorEffectHandles;

	UPROPERTY(ReplicatedUsing=OnRep_LastSkillUsed)
	FGameplayTag LastSkillUsed = FGameplayTag();

	UFUNCTION()
	void OnRep_LastSkillUsed(FGameplayTag OldLastSkillUsed);

private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32 XP = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_AttributePoints)
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_SpellPoints)
	int32 SpellPoints = 0;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);
};
