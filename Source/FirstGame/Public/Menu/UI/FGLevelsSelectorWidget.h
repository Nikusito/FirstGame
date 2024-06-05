// First Game

#pragma once

#include "CoreMinimal.h"
#include "UI/FGBaseWidget.h"
#include "FGCoreTypes.h"
#include "FGLevelsSelectorWidget.generated.h"

class UFGBaseButtonWidget;
class UHorizontalBox;
class UFGGameInstance;
class UFGLevelItemWidget;
class UImage;

UCLASS()
class FIRSTGAME_API UFGLevelsSelectorWidget : public UFGBaseWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelsItemBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelsItemWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UImage* LevelBackgroundImage;

	UPROPERTY(meta = (BindWidget))
	UFGBaseButtonWidget* SimpleButton;

	UPROPERTY(meta = (BindWidget))
	UFGBaseButtonWidget* MiddleButton;

	UPROPERTY(meta = (BindWidget))
	UFGBaseButtonWidget* HardButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* LoadAnimation;

	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
	UPROPERTY()
	TArray<UFGLevelItemWidget*>LevelItemWidgets;

	UFUNCTION()
	void OnSimpleGame();

	UFUNCTION()
	void OnMiddleGame();

	UFUNCTION()
	void OnHardGame();

	void OnStartGame();
	void InitLevelItems();
	void OnLevelSelected(const FLevelUIData& Data);
	UFGGameInstance* GetFGGameInstance() const;
};
