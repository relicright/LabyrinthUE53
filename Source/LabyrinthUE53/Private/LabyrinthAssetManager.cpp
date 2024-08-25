// Copyright Relic Rights Studio


#include "LabyrinthAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "LabyrinthGameplayTags.h"

ULabyrinthAssetManager& ULabyrinthAssetManager::Get()
{
	check(GEngine);
	
	ULabyrinthAssetManager* LabyrinthAssetManager = Cast<ULabyrinthAssetManager>(GEngine->AssetManager);
	return *LabyrinthAssetManager;
}

void ULabyrinthAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FLabyrinthGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
