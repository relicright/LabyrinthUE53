// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LabyrinthGameModeBase.generated.h"

class UArmorItemInfo;
class UAttributeXPLevelInfo;
class UAbilityInfo;
class UCharacterClassInfo;

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ALabyrinthGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UAttributeXPLevelInfo> AttributeXPLevelInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Info")
	TObjectPtr<UArmorItemInfo> ArmorItemInfo;
	
	// UPROPERTY(EditDefaultsOnly, Category = "Loot Tiers")
	// TObjectPtr<ULootTiers> LootTiers;
	//
	// void SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex);
	// ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const;
	// static void DeleteSlot(const FString& SlotName, int32 SlotIndex);
	// ULoadScreenSaveGame* RetrieveInGameSaveData();
	// void SaveInGameProgressData(ULoadScreenSaveGame* SaveObject);

	// void SaveWorldState(UWorld* World, const FString& DestinationMapAssetName = FString("")) const;
	// void LoadWorldState(UWorld* World) const;
	//
	// void TravelToMap(UMVVM_LoadSlot* Slot);

	// UPROPERTY(EditDefaultsOnly)
	// TSubclassOf<USaveGame> LoadScreenSaveGameClass;

	// UPROPERTY(EditDefaultsOnly)
	// FString DefaultMapName;

	// UPROPERTY(EditDefaultsOnly)
	// TSoftObjectPtr<UWorld> DefaultMap;
	//
	// UPROPERTY(EditDefaultsOnly)
	// FName DefaultPlayerStartTag;
	//
	// UPROPERTY(EditDefaultsOnly)
	// TMap<FString, TSoftObjectPtr<UWorld>> Maps;
	//
	// FString GetMapNameFromMapAssetName(const FString& MapAssetName) const;
	//
	// virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	void PlayerDied(ACharacter* DeadCharacter);
protected:
	virtual void BeginPlay() override;
};
