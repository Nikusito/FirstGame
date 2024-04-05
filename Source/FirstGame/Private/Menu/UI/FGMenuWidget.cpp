// First Game

#include "Menu/UI/FGMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UFGMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton) 
	{
		StartGameButton->OnClicked.AddDynamic(this, &UFGMenuWidget::OnStartGame);
	}
}

void UFGMenuWidget::OnStartGame()
{
	const FName StartupLevelName = "DevMap";
	UGameplayStatics::OpenLevel(this, StartupLevelName);
}
