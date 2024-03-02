// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FGGameHUD.generated.h"

UCLASS()
class FIRSTGAME_API AFGGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>PlayerWidgetClass;

	virtual void BeginPlay() override;
};
