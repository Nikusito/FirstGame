// First Game

#include "Menu/UI/FGMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AFGMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass) 
	{
		const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget) 
		{
			MenuWidget->AddToViewport();
		}
	}
}
