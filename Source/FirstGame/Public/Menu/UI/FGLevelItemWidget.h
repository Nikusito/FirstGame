// First Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGCoreTypes.h"
#include "FGLevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class FIRSTGAME_API UFGLevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnLevelSelectedSignature OnLevelSelected;

	void SetLevelData(const FLevelUIData& Data);
	FLevelUIData GetLevelData() const { return LevelUIData; }

	void SetSelected(bool IsSelected);
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* LevelImage;

	UPROPERTY(meta = (BindWidget))
	UImage* FrameImage;

	virtual void NativeOnInitialized() override;

private:
	FLevelUIData LevelUIData;

	UFUNCTION()
	void OnLevelItemClicked();

	UFUNCTION()
	void OnLevelItemHovered();

	UFUNCTION()
	void OnLevelItemUnhovered();
};
