// First Game

#include "Menu/UI/FGMenuWidget.h"
#include "UI/FGBaseButtonWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "FGGameInstance.h"
#include "Menu/FGMenuGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/FGSoundFunctLib.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGMenuWidget, All, All)

void UFGMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartLevelSelectorButton)
	{
		StartLevelSelectorButton->BaseButton->OnClicked.AddDynamic(this, &UFGMenuWidget::OnStartLevelSelector);
		StartLevelSelectorButton->SetNameButton(FText::FromString("Start Game"));
	}

	if (QuitGameButton)
	{
		QuitGameButton->BaseButton->OnClicked.AddDynamic(this, &UFGMenuWidget::OnQuitGame);
		QuitGameButton->SetNameButton(FText::FromString("Quit Game"));
	}

	if (RulesButton)
	{
		RulesButton->BaseButton->OnClicked.AddDynamic(this, &UFGMenuWidget::OnRulesGame);
		RulesButton->SetNameButton(FText::FromString("Rules Game"));
	}

	if (SoundSlider)
	{
		SoundSlider->OnValueChanged.AddDynamic(this, &UFGMenuWidget::OnRegulateSound);
	}
}

void UFGMenuWidget::OnStartLevelSelector()
{
	if (!GetWorld()) return;

	const auto MenuGameMode = GetFGMenuGameModeBase();
	if (!MenuGameMode) return;

	MenuGameMode->SetUIState(EFGUIState::LevelsSelector);
}

void UFGMenuWidget::OnRulesGame()
{
	if (!GetWorld()) return;

	const auto MenuGameMode = GetFGMenuGameModeBase();
	if (!MenuGameMode) return;

	MenuGameMode->SetUIState(EFGUIState::HelpAndSetting);
}

void UFGMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UFGMenuWidget::OnRegulateSound(float Value)
{
	UFGSoundFunctLib::SetSoundClassVolume(MasterSoundClass, Value);
}

AFGMenuGameModeBase* UFGMenuWidget::GetFGMenuGameModeBase() const
{
	if (!GetWorld()) return nullptr;

	const auto MenuGameMode = Cast<AFGMenuGameModeBase>(GetWorld()->GetAuthGameMode());
	return MenuGameMode;
}
