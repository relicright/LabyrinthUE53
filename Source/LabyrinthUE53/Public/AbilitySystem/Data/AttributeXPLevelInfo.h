// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttributeXPLevelInfo.generated.h"

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API UAttributeXPLevelInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Attributes|XPRequirements")
	TObjectPtr<UCurveTable> AttributeSkillXPRequirements;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes|XPRequirements")
	TObjectPtr<UCurveTable> AttributeSecondarySkillXPRequirements;
};
