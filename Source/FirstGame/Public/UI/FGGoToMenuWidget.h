// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGGoToMenuWidget.generated.h"

class UButton;

UCLASS()
class FIRSTGAME_API UFGGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* GoToMenuButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnGoToMenu();
};
