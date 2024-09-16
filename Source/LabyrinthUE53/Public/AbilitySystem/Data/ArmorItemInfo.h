// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/LabyrinthAttributeSet.h"
#include "ArmorItemInfo.generated.h"

struct FGameplayTag;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Shotty,
	Rusty,
	Ordinary,
	Exceptional,
	Rare,
	Legendary,
	Artifact
};

USTRUCT(BlueprintType)
struct FArmorItemDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category= "ItemInfo")
	TSubclassOf<UGameplayEffect> PrimaryGameplayEffect;

	UPROPERTY(EditDefaultsOnly, Category= "ItemInfo")
	TSubclassOf<UGameplayAbility> PrimaryGameplayAbility;

	UPROPERTY(EditDefaultsOnly, Category= "ItemInfo")
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, Category= "ItemInfo")
	FName ItemDescription;

	UPROPERTY(EditDefaultsOnly, Category= "ItemInfo")
	FGameplayTag EquipmentSlotTag;
};



/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API UArmorItemInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Armor Item Defaults")
	TMap<FGameplayTag, FArmorItemDefaultInfo> ArmorItemInformation;

	// UPROPERTY(EditDefaultsOnly, Category = "Armor Item Defaults")
	// TObjectPtr<UCurveTable> ArmorItemStatLevels;
	
	FArmorItemDefaultInfo GetArmorItemInfo(FGameplayTag Tag);

	// TODO: Make a way to find specific curve table needed for different types of armor based on the item cost (maybe change to level)
};
