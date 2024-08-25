// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LabyrinthAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ULabyrinthAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:

	static ULabyrinthAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;

};
