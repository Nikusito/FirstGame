// First Game

#include "Menu/UI/FGGoBackWidget.h"
#include "Components/Button.h"
#include "Menu/FGMenuGameModeBase.h"

void UFGGoBackWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoBackButton)
	{
		GoBackButton->OnClicked.AddDynamic(this, &UFGGoBackWidget::OnGoBack);
	}
}

void UFGGoBackWidget::OnGoBack()
{
	if (!GetWorld()) return;

	const auto MenuGameMode = Cast<AFGMenuGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!MenuGameMode) return;

	MenuGameMode->SetUIState(EFGUIState::StartMenu);
}
