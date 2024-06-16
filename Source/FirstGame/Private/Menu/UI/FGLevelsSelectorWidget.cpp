// First Game

#include "Menu/UI/FGLevelsSelectorWidget.h"
#include "FGGameInstance.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "UI/FGBaseButtonWidget.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/FGLevelItemWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void UFGLevelsSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitLevelItems();

	if (SimpleButton)
	{
		SimpleButton->BaseButton->OnClicked.AddDynamic(this, &UFGLevelsSelectorWidget::OnSimpleGame);
		SimpleButton->SetNameButton(FText::FromString("Simple"));
	}

	if (MiddleButton)
	{
		MiddleButton->BaseButton->OnClicked.AddDynamic(this, &UFGLevelsSelectorWidget::OnMiddleGame);
		MiddleButton->SetNameButton(FText::FromString("Middle"));
	}

	if (HardButton)
	{
		HardButton->BaseButton->OnClicked.AddDynamic(this, &UFGLevelsSelectorWidget::OnHardGame);
		HardButton->SetNameButton(FText::FromString("Hard"));
	}
}

void UFGLevelsSelectorWidget::InitLevelItems()
{
	const auto FGGameInstance = GetFGGameInstance();
	if (!FGGameInstance) return;

	checkf(FGGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be Empty!"));

	if (!LevelsItemBox) return;
	LevelsItemBox->ClearChildren();

	for (auto LevelUIData: FGGameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<UFGLevelItemWidget>(GetWorld(), LevelsItemWidgetClass);
		if (!LevelItemWidget) continue;

		LevelItemWidget->SetLevelData(LevelUIData);
		LevelItemWidget->OnLevelSelected.AddUObject(this, &UFGLevelsSelectorWidget::OnLevelSelected);

		LevelsItemBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}

	if (FGGameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(FGGameInstance->GetLevelsData()[0]);
	}
	else 
	{
		OnLevelSelected(FGGameInstance->GetStartupLevel());
	}
}

void UFGLevelsSelectorWidget::OnLevelSelected(const FLevelUIData& Data)
{
	const auto FGGameInstance = GetFGGameInstance();
	if (!FGGameInstance) return;

	FGGameInstance->SetStartupLevel(Data);

	for (auto LevelItemWidget : LevelItemWidgets) 
	{
		if (LevelItemWidget) 
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
			LevelBackgroundImage->SetBrushFromTexture(Data.LevelBackground);
		}
	}
}

void UFGLevelsSelectorWidget::OnStartGame()
{
	PlayAnimation(LoadAnimation);
	UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void UFGLevelsSelectorWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation != LoadAnimation) return;

	const auto FGGameInstance = GetFGGameInstance();
	if (!FGGameInstance) return;

	UGameplayStatics::OpenLevel(this, FGGameInstance->GetStartupLevel().LevelName);
}

void UFGLevelsSelectorWidget::OnSimpleGame()
{
	const auto FGGameInstance = GetFGGameInstance();
	if (!FGGameInstance) return;

	FGGameInstance->SetDifficultyLevel(EFGDifficulty::Simple);

	OnStartGame();
}

void UFGLevelsSelectorWidget::OnMiddleGame()
{
	const auto FGGameInstance = GetFGGameInstance();
	if (!FGGameInstance) return;

	FGGameInstance->SetDifficultyLevel(EFGDifficulty::Middle);

	OnStartGame();
}

void UFGLevelsSelectorWidget::OnHardGame()
{
	const auto FGGameInstance = GetFGGameInstance();
	if (!FGGameInstance) return;

	FGGameInstance->SetDifficultyLevel(EFGDifficulty::Hard);

	OnStartGame();
}

UFGGameInstance* UFGLevelsSelectorWidget::GetFGGameInstance() const
{
	if(!GetWorld()) return nullptr;
	
	return GetWorld()->GetGameInstance<UFGGameInstance>();
}
