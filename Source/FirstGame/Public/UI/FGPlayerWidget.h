// First Game

#pragma once

#include "CoreMinimal.h"
#include "UI/FGBaseWidget.h"
#include "FGCoreTypes.h"
#include "FGPlayerWidget.generated.h"

class AFGGameModeBase;

UCLASS()
class FIRSTGAME_API UFGPlayerWidget : public UFGBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	AFGGameModeBase* GetFGGameMode() const;
};
