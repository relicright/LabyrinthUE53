// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_RotateTowards.generated.h"

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API UBTTask_RotateTowards : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	
};
