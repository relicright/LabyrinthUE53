// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LabyrinthAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ALabyrinthAIController : public AAIController
{
	GENERATED_BODY()

public:
	ALabyrinthAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
