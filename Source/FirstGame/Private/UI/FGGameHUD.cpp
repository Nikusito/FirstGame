// First Game

#include "UI/FGGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "FGGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGGameHUD, All, All)

void AFGGameHUD::BeginPlay() 
{
	Super::BeginPlay();

	GameWidgets.Add(EFGMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass));
	GameWidgets.Add(EFGMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EFGMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

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
		const auto GameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode) 
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
	}
	UE_LOG(LogFGGameHUD, Display, TEXT("Match state: %s"), *UEnum::GetValueAsString(State));
}