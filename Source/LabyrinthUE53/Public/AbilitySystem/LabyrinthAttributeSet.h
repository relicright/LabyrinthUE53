// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "LabyrinthAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

// typedef is specific to the FGameplayAttribute() signature, but TStaticFunPtr is generic to any signature chosen
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ULabyrinthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	ULabyrinthAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	UFUNCTION(BlueprintCallable)
	void SendXPEvent(const FEffectProperties& Props);

	/*
	 * Primary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dexterity, Category = "Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Dexterity);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Constitution, Category = "Primary Attributes")
	FGameplayAttributeData Constitution;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Constitution);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Wisdom, Category = "Primary Attributes")
	FGameplayAttributeData Wisdom;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Wisdom);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Luck, Category = "Primary Attributes")
	FGameplayAttributeData Luck;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Luck);

	/*
	 * Secondary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, ArmorPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, BlockChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, CriticalHitResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, ManaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Vital Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, MaxStamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MoveSpeed, Category = "Vital Attributes")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, MoveSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseMoveSpeed, Category = "Vital Attributes")
	FGameplayAttributeData BaseMoveSpeed;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, BaseMoveSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorMoveSpeed, Category = "Vital Attributes")
	FGameplayAttributeData ArmorMoveSpeed;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, ArmorMoveSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BuffMoveSpeed, Category = "Vital Attributes")
	FGameplayAttributeData BuffMoveSpeed;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, BuffMoveSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WeightMoveSpeed, Category = "Vital Attributes")
	FGameplayAttributeData WeightMoveSpeed;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, WeightMoveSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CarryCapacity, Category = "Capacity Attributes")
	FGameplayAttributeData CarryCapacity;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, CarryCapacity);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentWeight, Category = "Capacity Attributes")
	FGameplayAttributeData CurrentWeight;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, CurrentWeight);

	/*
	 * Primary Skill Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Arcanist, Category = "Primary Skill Attributes")
	FGameplayAttributeData Arcanist;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Arcanist);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Religion, Category = "Primary Skill Attributes")
	FGameplayAttributeData Religion;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Religion);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Martial, Category = "Primary Skill Attributes")
	FGameplayAttributeData Martial;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Martial);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Tracker, Category = "Primary Skill Attributes")
	FGameplayAttributeData Tracker;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Tracker);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Scoundrel, Category = "Primary Skill Attributes")
	FGameplayAttributeData Scoundrel;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Scoundrel);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Alchemist, Category = "Primary Skill Attributes")
	FGameplayAttributeData Alchemist;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Alchemist);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Constructor, Category = "Primary Skill Attributes")
	FGameplayAttributeData Constructor;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Constructor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Summoner, Category = "Primary Skill Attributes")
	FGameplayAttributeData Summoner;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Summoner);

	/*
	 * Secondary Skill Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Acrobatics, Category = "Secondary Skill Attributes")
	FGameplayAttributeData Acrobatics;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Acrobatics);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Athletics, Category = "Secondary Skill Attributes")
	FGameplayAttributeData Athletics;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Athletics);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Perception, Category = "Secondary Skill Attributes")
	FGameplayAttributeData Perception;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Perception);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Survival, Category = "Secondary Skill Attributes")
	FGameplayAttributeData Survival;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Survival);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stealth, Category = "Secondary Skill Attributes")
    FGameplayAttributeData Stealth;
    ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Stealth);
    	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Musicianship, Category = "Secondary Skill Attributes")
	FGameplayAttributeData Musicianship;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Musicianship);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Thievery, Category = "Secondary Skill Attributes")
	FGameplayAttributeData Thievery;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Thievery);
	

	/*
	 * Resistance Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category = "Resistance Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, FireResistance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category = "Resistance Attributes")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, LightningResistance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArcaneResistance, Category = "Resistance Attributes")
	FGameplayAttributeData ArcaneResistance;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, ArcaneResistance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Resistance Attributes")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, PhysicalResistance);

	/*
	 * Vital Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, Stamina);


	/*
	 * Meta Attributes
	 */

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, IncomingDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(ULabyrinthAttributeSet, IncomingXP);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;

	UFUNCTION()
	void OnRep_Constitution(const FGameplayAttributeData& OldConstitution) const;

	UFUNCTION()
	void OnRep_Wisdom(const FGameplayAttributeData& OldWisdom) const;

	UFUNCTION()
	void OnRep_Luck(const FGameplayAttributeData& OldLuck) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

	UFUNCTION()
	void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed) const;

	UFUNCTION()
	void OnRep_BaseMoveSpeed(const FGameplayAttributeData& OldBaseMoveSpeed) const;

	UFUNCTION()
	void OnRep_ArmorMoveSpeed(const FGameplayAttributeData& OldBaseMoveSpeed) const;

	UFUNCTION()
	void OnRep_BuffMoveSpeed(const FGameplayAttributeData& OldBaseMoveSpeed) const;

	UFUNCTION()
	void OnRep_WeightMoveSpeed(const FGameplayAttributeData& OldMoveSpeed) const;

	UFUNCTION()
	void OnRep_CarryCapacity(const FGameplayAttributeData& OldCarryCapacity) const;

	UFUNCTION()
	void OnRep_CurrentWeight(const FGameplayAttributeData& OldCarryWeight) const;
	
	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;

	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;

	UFUNCTION()
	void OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const;

	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const;

	UFUNCTION()
	void OnRep_Arcanist(const FGameplayAttributeData& OldArcanist) const;

	UFUNCTION()
	void OnRep_Religion(const FGameplayAttributeData& OldReligion) const;

	UFUNCTION()
	void OnRep_Martial(const FGameplayAttributeData& OldMartial) const;

	UFUNCTION()
	void OnRep_Tracker(const FGameplayAttributeData& OldTracker) const;	

	UFUNCTION()
	void OnRep_Scoundrel(const FGameplayAttributeData& OldScoundrel) const;

	UFUNCTION()
	void OnRep_Alchemist(const FGameplayAttributeData& OldAlchemist) const;

	UFUNCTION()
	void OnRep_Constructor(const FGameplayAttributeData& OldConstructor) const;

	UFUNCTION()
	void OnRep_Summoner(const FGameplayAttributeData& OldPhysicalResistance) const;

	UFUNCTION()
	void OnRep_Acrobatics(const FGameplayAttributeData& OldManaRegeneration) const;

	UFUNCTION()
	void OnRep_Athletics(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Perception(const FGameplayAttributeData& OldMaxMana) const;	

	UFUNCTION()
	void OnRep_Survival(const FGameplayAttributeData& OldFireResistance) const;

	UFUNCTION()
	void OnRep_Stealth(const FGameplayAttributeData& OldLightningResistance) const;

	UFUNCTION()
	void OnRep_Musicianship(const FGameplayAttributeData& OldArcaneResistance) const;

	UFUNCTION()
	void OnRep_Thievery(const FGameplayAttributeData& OldPhysicalResistance) const;

private:
	void HandleIncomingDamage(const FEffectProperties& Props);
	void HandleIncomingXP(const FEffectProperties& Props);
	void Debuff(const FEffectProperties& Props);
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const;
	int32 CalculateNewMoveSpeed();

	bool bTopOffHealth = false;
	bool bTopOffMana = false;
};




