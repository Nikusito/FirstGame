// First Game

#include "UI/FGPauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"
#include "UI/FGBaseButtonWidget.h"
#include "FGGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGPauseWidget, All, All)

void UFGPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton) 
	{
		ClearPauseButton->BaseButton->OnClicked.AddDynamic(this, &UFGPauseWidget::OnClearPause);
		ClearPauseButton->SetNameButton(FText::FromString("Continue"));
	}

	if (GoToMenuButton)
	{
		GoToMenuButton->BaseButton->OnClicked.AddDynamic(this, &UFGPauseWidget::OnGoToMenu);
		GoToMenuButton->SetNameButton(FText::FromString("Main Menu"));
	}
}

void UFGPauseWidget::OnClearPause() 
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}

void UFGPauseWidget::OnGoToMenu()
{
	if (!GetWorld())return;

	const auto FGGameInstance = GetWorld()->GetGameInstance<UFGGameInstance>();
	if (!FGGameInstance) return;

	if (FGGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogFGPauseWidget, Error, TEXT("Menu level name is NONE"));
		return;
	}
	UGameplayStatics::OpenLevel(this, FGGameInstance->GetMenuLevelName());
}