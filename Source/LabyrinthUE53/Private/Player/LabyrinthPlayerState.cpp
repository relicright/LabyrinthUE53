// Copyright Relic Rights Studio


#include "Player/LabyrinthPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/LabyrinthAbilitySystemComponent.h"
#include "AbilitySystem/LabyrinthAttributeSet.h"

ALabyrinthPlayerState::ALabyrinthPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<ULabyrinthAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<ULabyrinthAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

void ALabyrinthPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

UAbilitySystemComponent* ALabyrinthPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
