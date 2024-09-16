// Copyright Relic Rights Studio


#include "Actor/LabyrinthProjectile.h"

// Sets default values
ALabyrinthProjectile::ALabyrinthProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALabyrinthProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALabyrinthProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

