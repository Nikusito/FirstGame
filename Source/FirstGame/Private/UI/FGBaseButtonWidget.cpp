// First Game

#include "UI/FGBaseButtonWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UFGBaseButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BaseButton) 
	{
		BaseButton->OnHovered.AddDynamic(this, &UFGBaseButtonWidget::OnButtonHovered);
		BaseButton->OnUnhovered.AddDynamic(this, &UFGBaseButtonWidget::OnButtonUnhovered);
	}

	if (FrameLeftButtonImage && FrameRightButtonImage)
	{
		FrameLeftButtonImage->SetVisibility(ESlateVisibility::Hidden);
		FrameRightButtonImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UFGBaseButtonWidget::OnButtonHovered()
{
	if (FrameLeftButtonImage && FrameRightButtonImage) 
	{
		FrameLeftButtonImage->SetVisibility(ESlateVisibility::Visible);
		FrameRightButtonImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UFGBaseButtonWidget::OnButtonUnhovered()
{
	if (FrameLeftButtonImage && FrameRightButtonImage)
	{
		FrameLeftButtonImage->SetVisibility(ESlateVisibility::Hidden);
		FrameRightButtonImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UFGBaseButtonWidget::SetNameButton(FText Name)
{
	if (NameButton) 
	{
		NameButton->SetText(Name);
	}
}