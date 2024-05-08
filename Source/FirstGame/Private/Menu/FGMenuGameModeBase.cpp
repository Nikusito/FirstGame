// First Game

#include "Menu/FGMenuGameModeBase.h"
#include "Menu/FGMenuPlayerController.h"
#include "Menu/UI/FGMenuHUD.h"
#include "FGCoreTypes.h"

AFGMenuGameModeBase::AFGMenuGameModeBase() 
{
	PlayerControllerClass = AFGMenuPlayerController::StaticClass();
	HUDClass = AFGMenuHUD::StaticClass();
}


void AFGMenuGameModeBase::StartPlay()
{
	Super::StartPlay();

	SetUIState(EFGUIState::StartMenu);
}

void AFGMenuGameModeBase::SetUIState(EFGUIState State)
{
	OnUIStateChanged.Broadcast(State);
}