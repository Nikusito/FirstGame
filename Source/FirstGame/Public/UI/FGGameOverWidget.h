// First Game

#pragma once

#include "CoreMinimal.h"
#include "UI/FGBaseWidget.h"
#include "FGCoreTypes.h"
#include "FGGameOverWidget.generated.h"

class UTextBlock;
class UFGBaseButtonWidget;

UCLASS()
class FIRSTGAME_API UFGGameOverWidget : public UFGBaseWidget
{
	GENERATED_BODY()

public:
	void SetWinnOrLose(const bool& CheckSickPawn);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WinnOrLose;

	UPROPERTY(meta = (BindWidget))
	UFGBaseButtonWidget* ResetLevelButton;

	UPROPERTY(meta = (BindWidget))
	UFGBaseButtonWidget* GoToMenuButton;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnResetLevel();

	UFUNCTION()
	void OnGoToMenu();

	void OnMatchStateChanged(EFGMatchState State);
};
