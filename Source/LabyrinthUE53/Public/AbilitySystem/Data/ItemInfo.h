// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/LabyrinthAttributeSet.h"
#include "ItemInfo.generated.h"

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
struct FItemDefaultInfo
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
	TObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, Category= "ItemInfo")
	TObjectPtr<UTexture2D> ItemImage;

	UPROPERTY(EditDefaultsOnly, Category= "ItemInfo")
	FGameplayTag EquipmentSlotTag;
	
	UPROPERTY(EditDefaultsOnly, Category= "ItemInfo")
	int32 Weight;
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
	TMap<FGameplayTag, FItemDefaultInfo> ArmorItemInformation;

	FItemDefaultInfo GetArmorItemInfo(FGameplayTag Tag);
};
