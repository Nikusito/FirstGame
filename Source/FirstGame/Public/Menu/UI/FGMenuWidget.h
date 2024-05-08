// First Game

#pragma once

#include "CoreMinimal.h"
#include "UI/FGBaseWidget.h"
#include "FGCoreTypes.h"
#include "FGMenuWidget.generated.h"

class UFGBaseButtonWidget;

UCLASS()
class FIRSTGAME_API UFGMenuWidget : public UFGBaseWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UFGBaseButtonWidget* StartLevelSelectorButton;

	UPROPERTY(meta = (BindWidget))
	UFGBaseButtonWidget* RulesButton;

	UPROPERTY(meta = (BindWidget))
	UFGBaseButtonWidget* QuitGameButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartLevelSelector();
	
	UFUNCTION()
	void OnRulesGame();

	UFUNCTION()
	void OnQuitGame();
};
