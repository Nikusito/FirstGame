// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGCoreTypes.h"
#include "FGPlayerWidget.generated.h"

UCLASS()
class FIRSTGAME_API UFGPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure = false, Category = "UI")
	FCountTypePawn GetStartGameCountPawn();
};
