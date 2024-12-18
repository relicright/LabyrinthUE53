// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTags.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * //TEST
 */
class LABYRINTHUE53_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	int32 FindLevelForXP(int32 InXP) const;

	UFUNCTION(BlueprintNativeEvent)
	void AddXPToAttribute(FGameplayTag Tag, int32 InXP) const;

	UFUNCTION(BlueprintNativeEvent)
	FGameplayTag GetLastSkillUsed();

	UFUNCTION(BlueprintNativeEvent)
	void SetLastSkillUsed(FGameplayTag LastUsedSkillTag);
	
	UFUNCTION(BlueprintNativeEvent)
	int32 GetXP() const;
	
	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributePointsReward(int32 Level) const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPointsReward(int32 Level) const;
	
	UFUNCTION(BlueprintNativeEvent)
	void AddToXP(int32 InXP);

	UFUNCTION(BlueprintNativeEvent)
	void AddToPlayerLevel(int32 InPlayerLevel);

	UFUNCTION(BlueprintNativeEvent)
	void AddToAttributePoints(int32 InAttributePoints);

	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributePoints() const;

	UFUNCTION(BlueprintNativeEvent)
	void AddToSpellPoints(int32 InSpellPoints);

	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPoints() const;
	
	UFUNCTION(BlueprintNativeEvent)
	void LevelUp();

	UFUNCTION(BlueprintNativeEvent)
	void EquipArmor(const FGameplayTag& ArmorItem, FGameplayTag& ArmorSlotTag, const int32 Level);
	
	UFUNCTION(BlueprintNativeEvent)
	void UnEquipArmor(FGameplayTag ArmorSlotTag);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateMovementSpeed(int32 Speed);
};
