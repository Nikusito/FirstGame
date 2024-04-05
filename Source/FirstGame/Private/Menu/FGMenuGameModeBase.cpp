// First Game

#include "Menu/FGMenuGameModeBase.h"
#include "Menu/FGMenuPlayerController.h"
#include "Menu/UI/FGMenuHUD.h"

AFGMenuGameModeBase::AFGMenuGameModeBase() 
{
	PlayerControllerClass = AFGMenuPlayerController::StaticClass();
	HUDClass = AFGMenuHUD::StaticClass();
}