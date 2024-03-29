// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGCoreTypes.h"
#include "FGPlayerWidget.generated.h"

class AFGGameModeBase;

UCLASS()
class FIRSTGAME_API UFGPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	AFGGameModeBase* GetFGGameMode() const;
};
