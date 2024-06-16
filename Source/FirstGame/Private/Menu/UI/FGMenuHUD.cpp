// First Game

#include "Menu/UI/FGMenuHUD.h"
#include "UI/FGBaseWidget.h"
#include "Menu/FGMenuGameModeBase.h"

void AFGMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	MenuWidgets.Add(EFGUIState::StartMenu, CreateWidget<UFGBaseWidget>(GetWorld(), MenuWidgetClass));
	MenuWidgets.Add(EFGUIState::LevelsSelector, CreateWidget<UFGBaseWidget>(GetWorld(), LevelsSelectorClass));
	MenuWidgets.Add(EFGUIState::HelpAndSetting, CreateWidget<UFGBaseWidget>(GetWorld(), RulesClass));

	for (auto MenuWidgetPair : MenuWidgets)
	{
		const auto GameWidget = MenuWidgetPair.Value;
		if (GameWidget)
		{
			GameWidget->AddToViewport();
			GameWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (GetWorld())
	{
		if (const auto GameMode = Cast<AFGMenuGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnUIStateChanged.AddUObject(this, &AFGMenuHUD::OnUIStateChanged);
		}
	}
}

void AFGMenuHUD::OnUIStateChanged(EFGUIState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (MenuWidgets.Contains(State))
	{
		CurrentWidget = MenuWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}
}
