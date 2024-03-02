// First Game

#include "UI/FGGameHUD.h"
#include "Blueprint/UserWidget.h"

void AFGGameHUD::BeginPlay() 
{
	Super::BeginPlay();

	auto PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass);
	if (PlayerWidget) 
	{
		PlayerWidget->AddToViewport();
	}
}