// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGCoreTypes.h"
#include "FGSlimeCountWidget.generated.h"

class UTextBlock;

UCLASS()
class FIRSTGAME_API UFGSlimeCountWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetCountSlime(FCountTypePawn CountPawn);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CountSick;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CountDoctor;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CountAssistent;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CountWorker;

private:
	void SetCountSick(const FText& Text);
	void SetCountDoctor(const FText& Text);
	void SetCountAssistent(const FText& Text);
	void SetCountWorker(const FText& Text);
};
