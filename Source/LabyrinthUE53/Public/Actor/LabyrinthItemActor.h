// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabyrinthItemActor.generated.h"

UCLASS()
class LABYRINTHUE53_API ALabyrinthItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALabyrinthItemActor();

protected:

	UPROPERTY(EditDefaultsOnly, Category="Item")
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, Category="Item")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
private:

};
