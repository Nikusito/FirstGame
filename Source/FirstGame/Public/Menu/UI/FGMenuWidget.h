// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGMenuWidget.generated.h"

class UButton;

UCLASS()
class FIRSTGAME_API UFGMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnStartGame();
};
