// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGGoBackWidget.generated.h"

class UButton;

UCLASS()
class FIRSTGAME_API UFGGoBackWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* GoBackButton;
	
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnGoBack();
};
