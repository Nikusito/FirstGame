// First Game

#include "FGGameModeBase.h"
#include "FGCoreTypes.h"
#include "Player/FGPlayerController.h"
#include "Player/FGBaseCharacter.h"
#include "UI/FGGameHUD.h"

//Create a delegate to sign the widget when the health state changes

AFGGameModeBase::AFGGameModeBase() 
{
	DefaultPawnClass = AFGBaseCharacter::StaticClass();
	PlayerControllerClass = AFGPlayerController::StaticClass();
	HUDClass = AFGGameHUD::StaticClass();
}

//At game startup, subscribe to the artificial character's delegate on collision

void AFGGameModeBase::HealingPawn(const ETypePawn& PawnType)
{
	switch (PawnType)
	{
	case ETypePawn::Doctor:
	{
		CountPawns.CountDoctor++;
		break;
	}
	case ETypePawn::Assistant:
	{
		CountPawns.CountAssistent++;
		break;
	}
	case ETypePawn::Worker:
	{
		CountPawns.CountWorker++;
		break;
	}
	}
	CountPawns.CountSick--;
	
}

void AFGGameModeBase::InfactionPawn(const ETypePawn& PawnType)
{
	switch (PawnType)
	{
	case ETypePawn::Doctor:
	{
		CountPawns.CountDoctor--;
		break;
	}
	case ETypePawn::Assistant:
	{
		CountPawns.CountAssistent--;
		break;
	}
	case ETypePawn::Worker:
	{
		CountPawns.CountWorker--;
		break;
	}
	}
	CountPawns.CountSick++;
}

void AFGGameModeBase::SetStartCountPawn(const ETypePawn& PawnType, const bool Health)
{
	if (Health)
	{
		switch (PawnType)
		{
		case ETypePawn::Doctor:
		{
			CountPawns.CountDoctor++;
			break;
		}
		case ETypePawn::Assistant:
		{
			CountPawns.CountAssistent++;
			break;
		}
		case ETypePawn::Worker:
		{
			CountPawns.CountWorker++;
			break;
		}
		}
	}
	else
	{
		CountPawns.CountSick++;
	}
}