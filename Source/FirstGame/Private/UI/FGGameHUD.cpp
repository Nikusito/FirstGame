// First Game

#include "UI/FGGameHUD.h"
#include "UI/FGBaseWidget.h"
#include "FGGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGGameHUD, All, All)

void AFGGameHUD::BeginPlay() 
{
	Super::BeginPlay();

	GameWidgets.Add(EFGMatchState::InProgress, CreateWidget<UFGBaseWidget>(GetWorld(), PlayerWidgetClass));
	GameWidgets.Add(EFGMatchState::Pause, CreateWidget<UFGBaseWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EFGMatchState::GameOver, CreateWidget<UFGBaseWidget>(GetWorld(), GameOverWidgetClass));

	for (auto GameWidgetPair : GameWidgets) 
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (GameWidget) 
		{
			GameWidget->AddToViewport();
			GameWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (GetWorld())
	{
		if (const auto GameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AFGGameHUD::OnMatchStateChanged);
		}
	}
}

void AFGGameHUD::OnMatchStateChanged(EFGMatchState State) 
{
	if (CurrentWidget) 
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State)) 
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}
	UE_LOG(LogFGGameHUD, Display, TEXT("Match state: %s"), *UEnum::GetValueAsString(State));
}