// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGBaseButtonWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

UCLASS()
class FIRSTGAME_API UFGBaseButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* BaseButton;

	void SetNameButton(FText Name);

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* FrameLeftButtonImage;

	UPROPERTY(meta = (BindWidget))
	UImage* FrameRightButtonImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();
};
