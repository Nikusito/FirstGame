// First Game

#include "FGGameModeBase.h"
#include "FGCoreTypes.h"
#include "Player/FGPlayerController.h"
#include "Player/FGBaseCharacter.h"
#include "AI/FGAICharacter.h"
#include "UI/FGGameHUD.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGGameModeBase, All, All)

AFGGameModeBase::AFGGameModeBase() 
{
	DefaultPawnClass = AFGBaseCharacter::StaticClass();
	PlayerControllerClass = AFGPlayerController::StaticClass();
	HUDClass = AFGGameHUD::StaticClass();
}

//Spawn Pawn
void AFGGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	StartGame();
}

void AFGGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i<GameData.PlayersNum-1; ++i) 
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto FGAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(FGAIController);
		SetStartCountPawn(FGAIController);
		IsAIPawn(FGAIController);
	}

	OnChangedTypePawn.Broadcast(GameData.CountTypePawn);
}

UClass* AFGGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController) 
{
	if (InController && InController->IsA<AAIController>()) 
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AFGGameModeBase::IsAIPawn(AAIController* InConroller)
{
	const auto Pawn = Cast<AFGAICharacter>(InConroller->GetPawn());
	if (!Pawn) return;

	Pawn->OnHealthChanged.AddUObject(this, &AFGGameModeBase::HealingOrInfaction);
}

//Game timer
void AFGGameModeBase::StartGame()
{
	TimeCountDown = GameData.TimeGame;
	GetWorldTimerManager().SetTimer(GameTimeHandle, this, &AFGGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AFGGameModeBase::GameTimerUpdate()
{
	if (--TimeCountDown == 0) 
	{
		GetWorldTimerManager().ClearTimer(GameTimeHandle);
		UE_LOG(LogFGGameModeBase, Warning, TEXT("====Game Over====="));
	}
}

//At game startup, subscribe to the artificial character's delegate on collision
void AFGGameModeBase::HealingOrInfaction(const bool& Health, const ETypePawn& TypePawn)
{
	if (Health) 
	{
		HealingPawn(TypePawn);
	}
	else 
	{
		InfactionPawn(TypePawn);
	}

	OnChangedTypePawn.Broadcast(GameData.CountTypePawn);
}

void AFGGameModeBase::HealingPawn(const ETypePawn& PawnType)
{
	switch (PawnType)
	{
	case ETypePawn::Doctor:
	{
		GameData.CountTypePawn.CountDoctor++;
		break;
	}
	case ETypePawn::Assistant:
	{
		GameData.CountTypePawn.CountAssistent++;
		break;
	}
	case ETypePawn::Worker:
	{
		GameData.CountTypePawn.CountWorker++;
		break;
	}
	}
	GameData.CountTypePawn.CountSick--;
	
}

void AFGGameModeBase::InfactionPawn(const ETypePawn& PawnType)
{
	switch (PawnType)
	{
	case ETypePawn::Doctor:
	{
		GameData.CountTypePawn.CountDoctor--;
		break;
	}
	case ETypePawn::Assistant:
	{
		GameData.CountTypePawn.CountAssistent--;
		break;
	}
	case ETypePawn::Worker:
	{
		GameData.CountTypePawn.CountWorker--;
		break;
	}
	}
	GameData.CountTypePawn.CountSick++;
}

void AFGGameModeBase::SetStartCountPawn(const AAIController* ControllerPawn)
{
	const auto Pawn = Cast<AFGBaseCharacter>(ControllerPawn->GetPawn());
	if (!Pawn) return;

	if (Pawn->GetSettingPawn().HealthType)
	{
		switch (Pawn->GetSettingPawn().TypePawn)
		{
		case ETypePawn::Doctor:
		{
			GameData.CountTypePawn.CountDoctor++;
			break;
		}
		case ETypePawn::Assistant:
		{
			GameData.CountTypePawn.CountAssistent++;
			break;
		}
		case ETypePawn::Worker:
		{
			GameData.CountTypePawn.CountWorker++;
			break;
		}
		}
	}
	else
	{
		GameData.CountTypePawn.CountSick++;
	}
}

//UE_LOG(LogFGGameModeBase, Display, TEXT("Doctor: %i, Assistant: %i, Worker: %i, Sick: %i"), GameData.CountTypePawn.CountDoctor, GameData.CountTypePawn.CountAssistent, GameData.CountTypePawn.CountWorker, GameData.CountTypePawn.CountSick);