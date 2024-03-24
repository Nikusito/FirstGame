// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGTimerWidget.generated.h"

class AFGGameModeBase;

UCLASS()
class FIRSTGAME_API UFGTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetSecondsRemaining() const;

private:
	AFGGameModeBase* GetFGGameMode() const;
};
