// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FGCoreTypes.h"
#include "FGGameHUD.generated.h"

class UFGBaseWidget;

UCLASS()
class FIRSTGAME_API AFGGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>PlayerWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EFGMatchState, UFGBaseWidget*>GameWidgets;

	UPROPERTY()
	UFGBaseWidget* CurrentWidget = nullptr;

	void OnMatchStateChanged(EFGMatchState State);
};
