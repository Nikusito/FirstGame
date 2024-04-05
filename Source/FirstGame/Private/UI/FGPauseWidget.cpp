// First Game

#include "UI/FGPauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"

void UFGPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton) 
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UFGPauseWidget::OnClearPause);
	}
}

void UFGPauseWidget::OnClearPause() 
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}