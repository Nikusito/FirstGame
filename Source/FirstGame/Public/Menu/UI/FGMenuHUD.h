// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FGMenuHUD.generated.h"

UCLASS()
class FIRSTGAME_API AFGMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>MenuWidgetClass;

	virtual void BeginPlay() override;
};
