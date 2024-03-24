// First Game

#include "UI/FGPlayerWidget.h"
#include "FGGameModeBase.h"

AFGGameModeBase* UFGPlayerWidget::GetFGGameMode() const
{
	return GetWorld() ? Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}