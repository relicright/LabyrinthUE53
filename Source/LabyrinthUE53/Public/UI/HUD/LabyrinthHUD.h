// Copyright Relic Rights Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LabyrinthHUD.generated.h"

class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class ULabyrinthUserWidget;
struct FWidgetControllerParams;
class USpellMenuWidgetController;

/**
 * 
 */
UCLASS()
class LABYRINTHUE53_API ALabyrinthHUD : public AHUD
{
	GENERATED_BODY()

public:

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	//USpellMenuWidgetController* GetSpellMenuWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:


private:

	UPROPERTY()
	TObjectPtr<ULabyrinthUserWidget>  OverlayWidget;	

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULabyrinthUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

	// UPROPERTY()
	// TObjectPtr<USpellMenuWidgetController> SpellMenuWidgetController;
	//
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<USpellMenuWidgetController> SpellMenuWidgetControllerClass;
};
