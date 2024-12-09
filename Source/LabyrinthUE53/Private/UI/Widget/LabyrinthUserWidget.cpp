// Copyright Relic Rights Studio


#include "UI/Widget/LabyrinthUserWidget.h"

void ULabyrinthUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}