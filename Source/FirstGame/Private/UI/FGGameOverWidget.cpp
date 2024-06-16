// First Game

#include "UI/FGGameOverWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UI/FGBaseButtonWidget.h"
#include "FGGameModeBase.h"
#include "FGGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGGameOverWidget, All, All)

void UFGGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetWorld())
	{
		if (const auto GameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UFGGameOverWidget::OnMatchStateChanged);
		}
	}

	if (ResetLevelButton) 
	{
		ResetLevelButton->BaseButton->OnClicked.AddDynamic(this, &UFGGameOverWidget::OnResetLevel);
		ResetLevelButton->SetNameButton(FText::FromString("Reset Level"));
	}

	if (GoToMenuButton) 
	{
		GoToMenuButton->BaseButton->OnClicked.AddDynamic(this, &UFGGameOverWidget::OnGoToMenu);
		GoToMenuButton->SetNameButton(FText::FromString("Main Menu"));
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
		if (const auto GameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode()))
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

void UFGGameOverWidget::OnGoToMenu()
{
	if (!GetWorld())return;

	const auto FGGameInstance = GetWorld()->GetGameInstance<UFGGameInstance>();
	if (!FGGameInstance) return;

	if (FGGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogFGGameOverWidget, Error, TEXT("Menu level name is NONE"));
		return;
	}
	UGameplayStatics::OpenLevel(this, FGGameInstance->GetMenuLevelName());
}