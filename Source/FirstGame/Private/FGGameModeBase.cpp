// First Game

#include "FGGameModeBase.h"
#include "Player/FGPlayerController.h"
#include "Player/FGBasePawn.h"

AFGGameModeBase::AFGGameModeBase() 
{
	DefaultPawnClass = AFGBasePawn::StaticClass();
	PlayerControllerClass = AFGPlayerController::StaticClass();
}