// First Game

#include "UI/FGTimerWidget.h"
#include "FGGameModeBase.h"

int32 UFGTimerWidget::GetSecondsRemaining() const 
{
	const auto GameMode = GetFGGameMode();
	return GameMode ? GameMode->GetTimeSeconds() : 0;
}

AFGGameModeBase* UFGTimerWidget::GetFGGameMode() const 
{
	return GetWorld() ? Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}