// Copyright Relic Rights Studio


#include "AbilitySystem/LabyrinthAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "LabyrinthGameplayTags.h"

ULabyrinthAttributeSet::ULabyrinthAttributeSet()
{
	const FLabyrinthGameplayTags& GameplayTags = FLabyrinthGameplayTags::Get();

	/* Primary Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Dexterity, GetDexterityAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Constitution, GetConstitutionAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Wisdom, GetWisdomAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Luck, GetLuckAttribute);

	/* Secondary Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);	
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);

	/* Primary Skills Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_PrimarySkill_Arcanist, GetArcanistAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_PrimarySkill_Religion, GetReligionAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_PrimarySkill_Martial, GetMartialAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_PrimarySkill_Tracker, GetTrackerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_PrimarySkill_Scoundrel, GetScoundrelAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_PrimarySkill_Alchemist, GetAlchemistAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_PrimarySkill_Constructor, GetConstructorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_PrimarySkill_Summoner, GetSummonerAttribute);

	/* Secondary Skills Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_SecondarySkill_Acrobatics, GetAcrobaticsAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SecondarySkill_Athletics, GetAthleticsAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SecondarySkill_Perception, GetPerceptionAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SecondarySkill_Survival, GetSurvivalAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SecondarySkill_Stealth, GetStealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SecondarySkill_Musicianship, GetMusicianshipAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SecondarySkill_Thievery, GetThieveryAttribute);

	/* Vital Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Vital_Health, GetHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Vital_Mana, GetManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Vital_Stamina, GetStaminaAttribute);
	
	/* Resistance Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Arcane, GetArcaneResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Fire, GetFireResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Lightning, GetLightningResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Physical, GetPhysicalResistanceAttribute);
}

void ULabyrinthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary Attributes
	
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Constitution, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Wisdom, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Luck, COND_None, REPNOTIFY_Always);

	// Secondary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	// Primary Skill Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Arcanist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Religion, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Martial, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Tracker, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Scoundrel, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Alchemist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Constructor, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Summoner, COND_None, REPNOTIFY_Always);	
	
	// Resistance Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, ArcaneResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
	
	// Vital Attributes
	
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULabyrinthAttributeSet, Mana, COND_None, REPNOTIFY_Always);
}

void ULabyrinthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void ULabyrinthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void ULabyrinthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void ULabyrinthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Health, OldHealth);
}

void ULabyrinthAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Mana, OldMana);
}

void ULabyrinthAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Stamina, OldStamina);
}

void ULabyrinthAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Strength, OldStrength);
}

void ULabyrinthAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Intelligence, OldIntelligence);
}

void ULabyrinthAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Dexterity, OldDexterity);
}

void ULabyrinthAttributeSet::OnRep_Constitution(const FGameplayAttributeData& OldConstitution) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Constitution, OldConstitution);
}

void ULabyrinthAttributeSet::OnRep_Wisdom(const FGameplayAttributeData& OldWisdom) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Wisdom, OldWisdom);
}

void ULabyrinthAttributeSet::OnRep_Luck(const FGameplayAttributeData& OldLuck) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Luck, OldLuck);
}

void ULabyrinthAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Armor, OldArmor);
}

void ULabyrinthAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void ULabyrinthAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, BlockChance, OldBlockChance);
}

void ULabyrinthAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void ULabyrinthAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void ULabyrinthAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void ULabyrinthAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void ULabyrinthAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void ULabyrinthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, MaxHealth, OldMaxHealth);
}

void ULabyrinthAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, MaxMana, OldMaxMana);
}

void ULabyrinthAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, FireResistance, OldFireResistance);
}

void ULabyrinthAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, LightningResistance, OldLightningResistance);
}

void ULabyrinthAttributeSet::OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, ArcaneResistance, OldArcaneResistance);
}

void ULabyrinthAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, PhysicalResistance, OldPhysicalResistance);
}

void ULabyrinthAttributeSet::OnRep_Arcanist(const FGameplayAttributeData& OldArcanist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Arcanist, OldArcanist);
}

void ULabyrinthAttributeSet::OnRep_Religion(const FGameplayAttributeData& OldReligion) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Religion, OldReligion);
}

void ULabyrinthAttributeSet::OnRep_Martial(const FGameplayAttributeData& OldMartial) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Martial, OldMartial);
}

void ULabyrinthAttributeSet::OnRep_Tracker(const FGameplayAttributeData& OldTracker) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Tracker, OldTracker);
}

void ULabyrinthAttributeSet::OnRep_Scoundrel(const FGameplayAttributeData& OldScoundrel) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Scoundrel, OldScoundrel);
}

void ULabyrinthAttributeSet::OnRep_Alchemist(const FGameplayAttributeData& OldAlchemist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Alchemist, OldAlchemist);
}

void ULabyrinthAttributeSet::OnRep_Constructor(const FGameplayAttributeData& OldConstructor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Constructor, OldConstructor);
}

void ULabyrinthAttributeSet::OnRep_Summoner(const FGameplayAttributeData& OldSummoner) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Summoner, OldSummoner);
}

void ULabyrinthAttributeSet::OnRep_Acrobatics(const FGameplayAttributeData& OldAcrobatics) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Acrobatics, OldAcrobatics);
}

void ULabyrinthAttributeSet::OnRep_Athletics(const FGameplayAttributeData& OldAthletics) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Athletics, OldAthletics);
}

void ULabyrinthAttributeSet::OnRep_Perception(const FGameplayAttributeData& OldPerception) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Perception, OldPerception);
}

void ULabyrinthAttributeSet::OnRep_Survival(const FGameplayAttributeData& OldSurvival) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Survival, OldSurvival);
}

void ULabyrinthAttributeSet::OnRep_Stealth(const FGameplayAttributeData& OldSealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Stealth, OldSealth);
}

void ULabyrinthAttributeSet::OnRep_Musicianship(const FGameplayAttributeData& OldMusicianship) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Musicianship, OldMusicianship);
}

void ULabyrinthAttributeSet::OnRep_Thievery(const FGameplayAttributeData& OldThievery) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabyrinthAttributeSet, Thievery, OldThievery);
}
