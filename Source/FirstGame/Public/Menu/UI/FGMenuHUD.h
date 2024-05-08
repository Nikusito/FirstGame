// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FGCoreTypes.h"
#include "FGMenuHUD.generated.h"

class UFGBaseWidget;

UCLASS()
class FIRSTGAME_API AFGMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>LevelsSelectorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>RulesClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EFGUIState, UFGBaseWidget*>MenuWidgets;

	UPROPERTY()
	UFGBaseWidget* CurrentWidget = nullptr;

	void OnUIStateChanged(EFGUIState State);
};
