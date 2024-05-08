// First Game

#pragma once

#include "CoreMinimal.h"
#include "UI/FGBaseWidget.h"
#include "FGPauseWidget.generated.h"

class UFGBaseButtonWidget;

UCLASS()
class FIRSTGAME_API UFGPauseWidget : public UFGBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UFGBaseButtonWidget* ClearPauseButton;

	UPROPERTY(meta = (BindWidget))
	UFGBaseButtonWidget* GoToMenuButton;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnClearPause();

	UFUNCTION()
	void OnGoToMenu();
};
