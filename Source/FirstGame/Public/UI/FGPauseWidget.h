// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGPauseWidget.generated.h"

class UButton;

UCLASS()
class FIRSTGAME_API UFGPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnClearPause();
};
