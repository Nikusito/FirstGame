// First Game

#include "Menu/FGMenuPlayerController.h"

void AFGMenuPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}