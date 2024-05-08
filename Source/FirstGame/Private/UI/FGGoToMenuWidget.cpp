// First Game

#include "UI/FGGoToMenuWidget.h"
#include "Components/Button.h"
#include "Menu/FGMenuGameModeBase.h"
#include "FGGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGGoToMenuWidget, All, All)

void UFGGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton) 
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UFGGoToMenuWidget::OnGoToMenu);
	}
}

void UFGGoToMenuWidget::OnGoToMenu()
{
	if (!GetWorld()) return;

	const auto MenuGameMode = Cast<AFGMenuGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!MenuGameMode) return;

	MenuGameMode->SetUIState(EFGUIState::StartMenu);
}
