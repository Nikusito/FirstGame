// First Game

#include "UI/FGSlimeCountWidget.h"
#include "Components/TextBlock.h"
#include "FGUtils.h"

void UFGSlimeCountWidget::SetCountSlime(FCountTypePawn CountPawn) 
{
	SetCountSick(FGUtils::TextFromInt(CountPawn.CountSick));
	SetCountDoctor(FGUtils::TextFromInt(CountPawn.CountDoctor));
	SetCountAssistent(FGUtils::TextFromInt(CountPawn.CountAssistent));
	SetCountWorker(FGUtils::TextFromInt(CountPawn.CountWorker));
}

void UFGSlimeCountWidget::SetCountSick(const FText& Text)
{
	if (!CountSick) return;
	CountSick->SetText(Text);
}

void UFGSlimeCountWidget::SetCountDoctor(const FText& Text)
{
	if (!CountDoctor) return;
	CountDoctor->SetText(Text);
}

void UFGSlimeCountWidget::SetCountAssistent(const FText & Text)
{
	if (!CountAssistent) return;
	CountAssistent->SetText(Text);
}

void UFGSlimeCountWidget::SetCountWorker(const FText& Text)
{
	if (!CountWorker) return;
	CountWorker->SetText(Text);
}