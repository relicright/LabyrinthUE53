// Copyright Relic Rights Studio


#include "UI/WidgetController/LabyrinthWidgetController.h"

#include "AbilitySystem/LabyrinthAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/LabyrinthPlayerController.h"
#include "Player/LabyrinthPlayerState.h"

void ULabyrinthWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void ULabyrinthWidgetController::BroadcastInitialValues()
{
}

void ULabyrinthWidgetController::BindCallbacksToDependencies()
{
}

void ULabyrinthWidgetController::BroadcastAbilityInfo()
{
	if (!GetLabyrinthASC()->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		FLabyrinthAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(LabyrinthAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = LabyrinthAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		Info.StatusTag = LabyrinthAbilitySystemComponent->GetStatusFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	GetLabyrinthASC()->ForEachAbility(BroadcastDelegate);
}

ALabyrinthPlayerController* ULabyrinthWidgetController::GetLabyrinthPC()
{
	if (LabyrinthPlayerController == nullptr)
	{
		LabyrinthPlayerController = Cast<ALabyrinthPlayerController>(PlayerController);
	}
	return LabyrinthPlayerController;
}

ALabyrinthPlayerState* ULabyrinthWidgetController::GetLabyrinthPS()
{
	if (LabyrinthPlayerState == nullptr)
	{
		LabyrinthPlayerState = Cast<ALabyrinthPlayerState>(PlayerState);
	}
	return LabyrinthPlayerState;
}

ULabyrinthAbilitySystemComponent* ULabyrinthWidgetController::GetLabyrinthASC()
{
	if (LabyrinthAbilitySystemComponent == nullptr)
	{
		LabyrinthAbilitySystemComponent = Cast<ULabyrinthAbilitySystemComponent>(AbilitySystemComponent);
	}
	return LabyrinthAbilitySystemComponent;
}

ULabyrinthAttributeSet* ULabyrinthWidgetController::GetLabyrinthAS()
{
	if (LabyrinthAttributeSet == nullptr)
	{
		LabyrinthAttributeSet = Cast<ULabyrinthAttributeSet>(AttributeSet);
	}
	return LabyrinthAttributeSet;
}
