// First Game


#include "Menu/UI/FGLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UFGLevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelSelectButton) 
	{
		LevelSelectButton->OnClicked.AddDynamic(this, &UFGLevelItemWidget::OnLevelItemClicked);
		LevelSelectButton->OnHovered.AddDynamic(this, &UFGLevelItemWidget::OnLevelItemHovered);
		LevelSelectButton->OnUnhovered.AddDynamic(this, &UFGLevelItemWidget::OnLevelItemUnhovered);
	}
}

void UFGLevelItemWidget::OnLevelItemClicked()
{
	OnLevelSelected.Broadcast(LevelUIData);
}

void UFGLevelItemWidget::SetLevelData(const FLevelUIData& Data)
{
	LevelUIData = Data;

	if (LevelNameTextBlock) 
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
	}

	if (LevelImage) 
	{
		LevelImage->SetBrushFromTexture(Data.LevelThumb);
	}
}

void UFGLevelItemWidget::SetSelected(bool IsSelected)
{
	if (LevelImage) 
	{
		LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Gray : FLinearColor::White);
	}
}

void UFGLevelItemWidget::OnLevelItemHovered()
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UFGLevelItemWidget::OnLevelItemUnhovered()
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Hidden);
	}
}