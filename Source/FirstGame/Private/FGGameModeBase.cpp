// First Game

#include "FGGameModeBase.h"
#include "Player/FGPlayerController.h"
#include "Player/FGBaseCharacter.h"

AFGGameModeBase::AFGGameModeBase() 
{
	DefaultPawnClass = AFGBaseCharacter::StaticClass();
	PlayerControllerClass = AFGPlayerController::StaticClass();
}