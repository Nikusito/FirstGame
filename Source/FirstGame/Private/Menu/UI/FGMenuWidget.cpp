// First Game

#include "Menu/UI/FGMenuWidget.h"
#include "UI/FGBaseButtonWidget.h"
#include "Components/Button.h"
#include "FGGameInstance.h"
#include "Menu/FGMenuGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGMenuWidget, All, All)

void UFGMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartLevelSelectorButton)
	{
		StartLevelSelectorButton->BaseButton->OnClicked.AddDynamic(this, &UFGMenuWidget::OnStartLevelSelector);
		StartLevelSelectorButton->SetNameButton(FText::FromString("Start Game"));
	}

	if (QuitGameButton)
	{
		QuitGameButton->BaseButton->OnClicked.AddDynamic(this, &UFGMenuWidget::OnQuitGame);
		QuitGameButton->SetNameButton(FText::FromString("Quit Game"));
	}

	if (RulesButton)
	{
		RulesButton->BaseButton->OnClicked.AddDynamic(this, &UFGMenuWidget::OnRulesGame);
		RulesButton->SetNameButton(FText::FromString("Rules Game"));
	}
}

void UFGMenuWidget::OnStartLevelSelector()
{
	if (!GetWorld()) return;

	const auto MenuGameMode = Cast<AFGMenuGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!MenuGameMode) return;

	MenuGameMode->SetUIState(EFGUIState::LevelsSelector);
}

void UFGMenuWidget::OnRulesGame()
{
	if (!GetWorld()) return;

	const auto MenuGameMode = Cast<AFGMenuGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!MenuGameMode) return;

	MenuGameMode->SetUIState(EFGUIState::HelpAndSetting);
}

void UFGMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
