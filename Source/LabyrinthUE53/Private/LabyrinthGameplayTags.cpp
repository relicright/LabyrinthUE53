// Copyright Relic Rights Studio


#include "LabyrinthGameplayTags.h"
#include "GameplayTagsManager.h"

FLabyrinthGameplayTags FLabyrinthGameplayTags::GameplayTags;

void FLabyrinthGameplayTags::InitializeNativeGameplayTags()
{
	//TEST
	/*
	 * Primary Attributes
	 */
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases physical damage")
		);

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases magical damage")
		);

	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Dexterity"),
		FString("Increases Dodge and Armor Penetration")
		);

	GameplayTags.Attributes_Primary_Constitution = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Constitution"),
		FString("Increases Health maximum and regeneration rates")
		);

	GameplayTags.Attributes_Primary_Wisdom = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Wisdom"),
		FString("Increases religious and other damage")
		);

	GameplayTags.Attributes_Primary_Luck = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Luck"),
		FString("Increases all RNG chances")
		);

	/*
	 * Secondary Attributes
	 */
	
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves Block Chance")
		);

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Ignores Percentage of enemy Armor, increases Critical Hit Chance")
		);

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Chance to cut incoming damage in half")
		);

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Chance to double damage plus critical hit bonus")
		);

	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Bonus damage added when a critical hit is scored")
		);

	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("Reduces Critical Hit Chance of attacking enemies")
		);

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Amount of Health regenerated every 1 second")
		);

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Amount of Mana regenerated every 1 second")
		);

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Maximum amount of Health obtainable")
		);

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Maximum amount of Mana obtainable")
		);

	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxStamina"),
		FString("Maximum amount of Stamina obtainable")
		);

	GameplayTags.Attributes_Secondary_MoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MoveSpeed"),
		FString("Current movement speed")
		);

	GameplayTags.Attributes_Secondary_BaseMoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BaseMoveSpeed"),
		FString("Base movement speed")
		);

	GameplayTags.Attributes_Secondary_ArmorMoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorMoveSpeed"),
		FString("Armor movement speed")
		);
	
	GameplayTags.Attributes_Secondary_BuffMoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.BuffMoveSpeed"),
	FString("Buff movement speed")
	);

	GameplayTags.Attributes_Secondary_WeightMoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.WeightMoveSpeed"),
	FString("Weight movement speed")
	);

	GameplayTags.Attributes_Secondary_CarryCapacity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CarryCapacity"),
		FString("Current amount of weight player can carry")
		);

	GameplayTags.Attributes_Secondary_CurrentWeight = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CurrentWeight"),
		FString("Current amount of weight player is carrying")
		);

	/*
	* Primary Skill Attributes
	*/

	GameplayTags.Attributes_PrimarySkill = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PrimarySkill"),
		FString("Magical Casting Abilities")
		);

	GameplayTags.Attributes_PrimarySkill_Arcanist = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PrimarySkill.Arcanist"),
		FString("Magical Casting Abilities")
		);

	GameplayTags.Attributes_PrimarySkill_Religion = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PrimarySkill.Religion"),
		FString("Religious Casting Abilities")
		);

	GameplayTags.Attributes_PrimarySkill_Martial = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PrimarySkill.Martial"),
		FString("Weapon or Unarmed Using Abilities")
		);

	GameplayTags.Attributes_PrimarySkill_Tracker = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PrimarySkill.Tracker"),
		FString("Ranger and Tracking Abilities")
		);

	GameplayTags.Attributes_PrimarySkill_Scoundrel = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PrimarySkill.Scoundrel"),
		FString("Rouge Abilities")
		);

	GameplayTags.Attributes_PrimarySkill_Alchemist = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PrimarySkill.Alchemist"),
		FString("Alchemical Abilities")
		);

	GameplayTags.Attributes_PrimarySkill_Constructor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PrimarySkill.Constructor"),
		FString("Construction Abilities")
		);

	GameplayTags.Attributes_PrimarySkill_Summoner = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PrimarySkill.Summoner"),
		FString("Summoning Abilities")
		);

	/*
	* Secondary Skill Attributes
	*/

	GameplayTags.Attributes_SecondarySkill_Acrobatics = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.SecondarySkill.Acrobatics"),
		FString("Acrobatic Abilities")
		);

	GameplayTags.Attributes_SecondarySkill_Athletics = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.SecondarySkill.Athletics"),
		FString("Athletic Abilities")
		);

	GameplayTags.Attributes_SecondarySkill_Perception = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.SecondarySkill.Perception"),
		FString("Perception Abilities")
		);

	GameplayTags.Attributes_SecondarySkill_Survival = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.SecondarySkill.Survival"),
		FString("Survival Abilities")
		);

	GameplayTags.Attributes_SecondarySkill_Stealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.SecondarySkill.Stealth"),
		FString("Stealth Abilities")
		);

	GameplayTags.Attributes_SecondarySkill_Musicianship = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.SecondarySkill.Musicianship"),
		FString("Musician Abilities")
		);

	GameplayTags.Attributes_SecondarySkill_Thievery = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.SecondarySkill.Thievery"),
		FString("Thievery Abilities")
		);

	/*
	* Vital Attributes
	*/

	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Health"),
		FString("Health Attributes")
		);

	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Mana"),
		FString("Mana Attributes")
		);
	GameplayTags.Attributes_Vital_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Stamina"),
		FString("Stamina Attributes")
		);
	
	/*
	 * Input Tags
	 */
	
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
		);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
		);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
		);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
		);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
		);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
		);

	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Passive.1"),
		FString("Input Tag Passive Ability 1")
		);

	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Passive.2"),
		FString("Input Tag Passive Ability 2")
		);

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
		);

	/*
	 * Damage Types
	 */

	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire"),
		FString("Fire Damage Type")
		);
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning"),
		FString("Lightning Damage Type")
		);
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Arcane"),
		FString("Arcane Damage Type")
		);
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("Physical Damage Type")
		);

	/*
	 * Resistances
	 */

	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Arcane"),
		FString("Resistance to Arcane damage")
		);
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),
		FString("Resistance to Fire damage")
		);
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),
		FString("Resistance to Lightning damage")
		);
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"),
		FString("Resistance to Physical damage")
		);

	/*
		 * Debuffs
		 */

	GameplayTags.Debuff_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Arcane"),
		FString("Debuff for Arcane damage")
		);
	
	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Burn"),
		FString("Debuff for Fire damage")
		);
	
	GameplayTags.Debuff_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Physical"),
		FString("Debuff for Physical damage")
		);
	
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Stun"),
		FString("Debuff for Lightning damage")
		);
	

	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Chance"),
		FString("Debuff Chance")
		);
	
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Damage"),
		FString("Debuff Damage")
		);
	
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Duration"),
		FString("Debuff Duration")
		);
	
	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Frequency"),
		FString("Debuff Frequency")
		);
	
	/*
	 * Meta Attributes
	 */

	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Meta.IncomingXP"),
		FString("Incoming XP Meta Attribute")
		);

	/*
	 * Map of Damage Types to Resistances
	 */
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);

	/*
	 * Effects
	 */

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("Tag granted when Hit Reacting")
		);

	/*
	 * Abilities
	 */

	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.None"),
		FString("No Ability - like the nullptr for Ability Tags")
		);

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack Ability Tag")
		);

	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Summon"),
		FString("Summon Ability Tag")
		);

	/*
	 * Offensive Spells
	 */

	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.FireBolt"),
		FString("FireBolt Ability Tag")
		);

	GameplayTags.Abilities_Fire_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.FireBlast"),
		FString("FireBlast Ability Tag")
		);

	GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Lightning.Electrocute"),
		FString("Electrocute Ability Tag")
		);

	GameplayTags.Abilities_Arcane_ArcaneShards = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Arcane.ArcaneShards"),
		FString("Arcane Shards Ability Tag")
		);


	/* Passive */
	GameplayTags.Abilities_Passive_ListenForEvent = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Passive.ListenForEvent"),
			FString("Listen for Event")
			);
	
	/*
	 * Passive Spells
	 */
	
	GameplayTags.Abilities_Passive_LifeSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Passive.LifeSiphon"),
			FString("Life Siphon")
			);
	GameplayTags.Abilities_Passive_ManaSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Passive.ManaSiphon"),
			FString("Mana Siphon")
			);
	GameplayTags.Abilities_Passive_HaloOfProtection = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Passive.HaloOfProtection"),
			FString("Halo Of Protection")
			);
	

	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.HitReact"),
		FString("Hit React Ability")
		);

	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Eligible"),
		FString("Eligible Status")
		);

	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Equipped"),
		FString("Equipped Status")
		);

	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Locked"),
		FString("Locked Status")
		);

	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Unlocked"),
		FString("Unlocked Status")
		);

	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.None"),
		FString("Type None")
		);

	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Offensive"),
		FString("Type Offensive")
		);

	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Passive"),
		FString("Type Passive")
		);

	/*
	* Cooldown
	*/
	
	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Fire.FireBolt"),
		FString("FireBolt Cooldown Tag")
		);

	/*
	 * Combat Sockets
	 */

	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Weapon"),
		FString("Weapon")
		);

	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.RightHand"),
		FString("Right Hand")
		);
	
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.LeftHand"),
		FString("Left Hand")
		);

	GameplayTags.CombatSocket_Body = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Body"),
		FString("Body Part")
		);


	/*
	 * Equipment Armor Tags
	 */

	GameplayTags.Equipment_Armor_Chest = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Armor.Chest"),
		FString("Chest")
		);

	GameplayTags.Equipment_Armor_Feet = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Armor.Feet"),
		FString("Feet")
		);

	GameplayTags.Equipment_Armor_Helmet = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Armor.Helmet"),
		FString("Helmet")
		);

	GameplayTags.Equipment_Armor_Gloves = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Armor.Gloves"),
		FString("Gloves")
		);

	GameplayTags.Equipment_Armor_Legs = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Armor.Legs"),
		FString("Legs")
		);


	/*
	*  Equipment Weapon Tags
	*/

	GameplayTags.Equipment_Weapon_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Weapon.RightHand"),
		FString("Right Hand")
		);

	GameplayTags.Equipment_Weapon_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Weapon.LeftHand"),
		FString("Left Hand")
		);

	GameplayTags.Equipment_Weapon_TwoHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Weapon.TwoHand"),
		FString("Two Hand")
		);

	GameplayTags.Equipment_Consumable_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Weapon.Consumable1"),
		FString("Consumable 1")
		);

	GameplayTags.Equipment_Consumable_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Weapon.Consumable2"),
		FString("Consumable 2")
		);

	GameplayTags.Equipment_Consumable_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Equipment.Weapon.Consumable3"),
		FString("Consumable 3")
		);

	/*
	*  Armor Tags
	*/

	GameplayTags.Item_Armor_PlateHelm = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.PlateHelm"),
		FString("Plate Helm")
		);

	GameplayTags.Item_Armor_PlateChest= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.PlateChest"),
		FString("Plate Chest")
		);

	GameplayTags.Item_Armor_PlateGloves = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.PlateGloves"),
		FString("Plate Gloves")
		);

	GameplayTags.Item_Armor_PlatePants = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.PlatePants"),
		FString("Plate Pants")
		);

	GameplayTags.Item_Armor_PlateBoots = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.PlateBoots"),
		FString("Plate Boots")
		);

	GameplayTags.Item_Armor_LeatherHelm = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.LeatherHelm"),
		FString("Leather Helm")
		);

	GameplayTags.Item_Armor_LeatherChest= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.LeatherChest"),
		FString("Leather Chest")
		);

	GameplayTags.Item_Armor_LeatherGloves = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.LeatherGloves"),
		FString("Leather Gloves")
		);

	GameplayTags.Item_Armor_LeatherPants = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.LeatherPants"),
		FString("Leather Pants")
		);

	GameplayTags.Item_Armor_LeatherBoots = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.LeatherBoots"),
		FString("Leather Boots")
		);

	GameplayTags.Item_Armor_ClothHelm = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.ClothHelm"),
		FString("Cloth Helm")
		);

	GameplayTags.Item_Armor_LeatherChest= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.ClothChest"),
		FString("Cloth Chest")
		);

	GameplayTags.Item_Armor_ClothGloves = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.ClothGloves"),
		FString("Cloth Gloves")
		);

	GameplayTags.Item_Armor_ClothPants = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.ClothPants"),
		FString("Cloth Pants")
		);

	GameplayTags.Item_Armor_ClothBoots = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.ClothBoots"),
		FString("Cloth Boots")
		);
	
	/*
	*  Weapon Tags
	*/

	GameplayTags.Item_Weapon_LongSword = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.LongSword"),
		FString("Long Sword")
		);
	
	GameplayTags.Item_Weapon_ShortSword = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.ShortSword"),
		FString("Short Sword")
		);

	GameplayTags.Item_Weapon_BastardSword = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.BastardSword"),
		FString("Bastard Sword")
		);
	
	GameplayTags.Item_Weapon_Katana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.Katana"),
		FString("Katana Sword")
		);
	
	GameplayTags.Item_Weapon_Rapier = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.Rapier"),
		FString("Rapier Sword")
		);

	GameplayTags.Item_Weapon_DaggerMisericorde = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.DaggerMisericorde"),
		FString("Dagger Misericorde")
		);

	GameplayTags.Item_Weapon_DaggerAnelace = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.DaggerAnelace"),
		FString("Dagger Anelace")
		);
	
	GameplayTags.Item_Weapon_LongBow = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.LongBow"),
		FString("LongBow")
		);
	
	GameplayTags.Item_Weapon_Crossbow = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.Crossbow"),
		FString("Crossbow")
		);

	GameplayTags.Item_Weapon_Flail = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.Flail "),
		FString("Flail")
		);

	GameplayTags.Item_Weapon_Mace = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.Mace "),
		FString("Mace")
		);

	GameplayTags.Item_Weapon_Halberd = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.Halberd "),
		FString("Halberd")
		);

	GameplayTags.Item_Weapon_Spear = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.Spear "),
	FString("Spear")
	);

	GameplayTags.Item_Weapon_BattleAxe = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.BattleAxe "),
	FString("BattleAxe")
	);

	GameplayTags.Item_Weapon_Hatchet = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.Hatchet "),
	FString("Hatchet")
	);

	GameplayTags.Item_Weapon_Spellbook = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.Spellbook "),
	FString("Spellbook")
	);

	GameplayTags.Item_Weapon_Staff = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.Staff"),
	FString("Staff")
	);
	
	GameplayTags.Item_Weapon_DivineIdol = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Item.Weapon.DivineIdol"),
    FString("Divine Idol")
    );

	GameplayTags.Item_Weapon_HolySymbol = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.HolySymbol"),
	FString("Holy Symbol")
	);

	GameplayTags.Item_Weapon_Cudgel = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.Cudgel"),
	FString("Cudgel")
	);

	GameplayTags.Item_Weapon_Nunchaku = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.Nunchaku"),
	FString("Nunchaku")
	);

	GameplayTags.Item_Weapon_StarKnife = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.StarKnife"),
	FString("Star Knife")
	);

	GameplayTags.Item_Weapon_SpikedChain = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.SpikedChain"),
	FString("Spiked Chain")
	);

	GameplayTags.Item_Weapon_Katar = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.Katar"),
	FString("Katar")
	);

	GameplayTags.Item_Weapon_Sai = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Item.Weapon.Sai"),
	FString("Sai")
	);

	/*
	*  Consumable Tags
	*/

	GameplayTags.Item_Consumable_HealthPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Consumable.HealthPotion"),
		FString("Health Potion")
		);

	GameplayTags.Item_Consumable_ManaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Consumable.ManaPotion"),
		FString("Mana Potion")
		);

	GameplayTags.Item_Consumable_StaminaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Consumable.StaminaPotion"),
		FString("Stamina Potion")
		);

	GameplayTags.Item_Consumable_Caltrop = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Consumable.Caltrop"),
		FString("Caltrop")
		);
	
	/*
	 * Montage Tags
	 */

	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.1"),
		FString("Attack 1")
		);

	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.2"),
		FString("Attack 2")
		);

	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.3"),
		FString("Attack 3")
		);

	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.4"),
		FString("Attack 4")
		);

	/*
	 * Player Tags
	 */

	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.CursorTrace"),
		FString("Block tracing under the cursor")
		);

	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputHeld"),
		FString("Block Input Held callback for input")
		);

	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputPressed"),
		FString("Block Input Pressed callback for input")
		);

	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputReleased"),
		FString("Block Input Released callback for input")
		);

	/*
	 * GameplayCues
	 */

	GameplayTags.GameplayCue_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("GameplayCue.FireBlast"),
		FString("FireBlast GameplayCue Tag")
		);
}

