// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
struct FLabyrinthGameplayTags
{
public:
	static const FLabyrinthGameplayTags& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Constitution;
	FGameplayTag Attributes_Primary_Wisdom;
	FGameplayTag Attributes_Primary_Luck;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxStamina;
	FGameplayTag Attributes_Secondary_CarryCapacity;

	FGameplayTag Attributes_PrimarySkill;
	FGameplayTag Attributes_PrimarySkill_Arcanist;
	FGameplayTag Attributes_PrimarySkill_Religion;
	FGameplayTag Attributes_PrimarySkill_Martial;
	FGameplayTag Attributes_PrimarySkill_Tracker;
	FGameplayTag Attributes_PrimarySkill_Scoundrel;
	FGameplayTag Attributes_PrimarySkill_Alchemist;
	FGameplayTag Attributes_PrimarySkill_Constructor;
	FGameplayTag Attributes_PrimarySkill_Summoner;

	FGameplayTag Attributes_SecondarySkill_Acrobatics;
	FGameplayTag Attributes_SecondarySkill_Athletics;
	FGameplayTag Attributes_SecondarySkill_Perception;
	FGameplayTag Attributes_SecondarySkill_Survival;
	FGameplayTag Attributes_SecondarySkill_Stealth;
	FGameplayTag Attributes_SecondarySkill_Musicianship;
	FGameplayTag Attributes_SecondarySkill_Thievery;

	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;
	FGameplayTag Attributes_Vital_Stamina;
	
	FGameplayTag Attributes_Meta_IncomingXP;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_Passive_1;
	FGameplayTag InputTag_Passive_2;

	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;

	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;

	FGameplayTag Debuff_Burn;
	FGameplayTag Debuff_Stun;
	FGameplayTag Debuff_Arcane;
	FGameplayTag Debuff_Physical;
	
	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Damage;
	FGameplayTag Debuff_Duration;
	FGameplayTag Debuff_Frequency;

	FGameplayTag Abilities_None;
	
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;
	
	FGameplayTag Abilities_HitReact;

	FGameplayTag Abilities_Status_Locked;
	FGameplayTag Abilities_Status_Eligible;
	FGameplayTag Abilities_Status_Unlocked;
	FGameplayTag Abilities_Status_Equipped;

	FGameplayTag Abilities_Type_Offensive;
	FGameplayTag Abilities_Type_Passive;
	FGameplayTag Abilities_Type_None;
	
	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag Abilities_Fire_FireBlast;	
	FGameplayTag Abilities_Lightning_Electrocute;
	FGameplayTag Abilities_Arcane_ArcaneShards;

	FGameplayTag Abilities_Passive_ListenForEvent;
	
	FGameplayTag Abilities_Passive_HaloOfProtection;
	FGameplayTag Abilities_Passive_LifeSiphon;
	FGameplayTag Abilities_Passive_ManaSiphon;

	FGameplayTag Cooldown_Fire_FireBolt;

	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Body;

	FGameplayTag Equipment_Armor_Helmet;
	FGameplayTag Equipment_Armor_Chest;
	FGameplayTag Equipment_Armor_Gloves;
	FGameplayTag Equipment_Armor_Legs;
	FGameplayTag Equipment_Armor_Feet;

	FGameplayTag Item_Armor_PlateHelm;
	FGameplayTag Item_Armor_PlateGloves;
	FGameplayTag Item_Armor_PlateChest;
	FGameplayTag Item_Armor_PlateBoots;
	FGameplayTag Item_Armor_PlatePants;

	FGameplayTag Item_Armor_LeatherHelm;
	FGameplayTag Item_Armor_LeatherGloves;
	FGameplayTag Item_Armor_LeatherChest;
	FGameplayTag Item_Armor_LeatherBoots;
	FGameplayTag Item_Armor_LeatherPants;

	FGameplayTag Item_Armor_ClothHelm;
	FGameplayTag Item_Armor_ClothGloves;
	FGameplayTag Item_Armor_ClothChest;
	FGameplayTag Item_Armor_ClothBoots;
	FGameplayTag Item_Armor_ClothPants;

	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;
	
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;

	FGameplayTag Effects_HitReact;

	FGameplayTag Player_Block_InputPressed;
	FGameplayTag Player_Block_InputHeld;
	FGameplayTag Player_Block_InputReleased;
	FGameplayTag Player_Block_CursorTrace;

	FGameplayTag GameplayCue_FireBlast;

private:
	static FLabyrinthGameplayTags GameplayTags;
};
