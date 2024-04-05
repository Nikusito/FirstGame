// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGCoreTypes.h"
#include "FGGameOverWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class FIRSTGAME_API UFGGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetWinnOrLose(const bool& CheckSickPawn);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WinnOrLose;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnResetLevel();

	void OnMatchStateChanged(EFGMatchState State);
};
