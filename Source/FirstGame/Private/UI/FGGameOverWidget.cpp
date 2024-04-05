// First Game

#include "UI/FGGameOverWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "FGGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UFGGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetWorld())
	{
		const auto GameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UFGGameOverWidget::OnMatchStateChanged);
		}
	}

	if (ResetLevelButton) 
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &UFGGameOverWidget::OnResetLevel);
	}
}

void UFGGameOverWidget::SetWinnOrLose(const bool& CheckSickPawn)
{
	if (CheckSickPawn) 
	{
		WinnOrLose->SetText(FText::FromString("You Winner"));
	}
	else 
	{
		WinnOrLose->SetText(FText::FromString("You Lose"));
	}
}

void UFGGameOverWidget::OnMatchStateChanged(EFGMatchState State) 
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	if (State == EFGMatchState::GameOver) 
	{
		const auto GameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			SetWinnOrLose(GameMode->CheckSickPawn());
		}
	}
}

void UFGGameOverWidget::OnResetLevel() 
{
	const FString CurrentLevel = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevel));
}