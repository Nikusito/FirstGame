// First Game

#include "FGGameModeBase.h"
#include "FGCoreTypes.h"
#include "Player/FGPlayerController.h"
#include "Player/FGBaseCharacter.h"
#include "AI/FGAICharacter.h"
#include "UI/FGGameHUD.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "FGGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGGameModeBase, All, All)

AFGGameModeBase::AFGGameModeBase() 
{
	DefaultPawnClass = AFGBaseCharacter::StaticClass();
	PlayerControllerClass = AFGPlayerController::StaticClass();
	HUDClass = AFGGameHUD::StaticClass();
}

void AFGGameModeBase::SetLevelSetting() 
{
	if (!GetWorld()) return;

	const auto GameInstance = GetWorld()->GetGameInstance<UFGGameInstance>();
	if (!GameInstance) return;

	if (GameData.LevelsSetting.Contains(GameInstance->GetDifficultyLevel()))
	{
		LevelSetting = GameData.LevelsSetting[GameInstance->GetDifficultyLevel()];
		CountType = LevelSetting.CountTypePawn;
		TimeCountDown = LevelSetting.TimeGame;
		TimeReHealing = LevelSetting.TimeReHealing;
	}
}

//Spawn Pawn
void AFGGameModeBase::StartPlay()
{
	Super::StartPlay();

	SetLevelSetting();

	checkf((CountType.CountSick + CountType.CountDoctor + CountType.CountAssistent + CountType.CountWorker) == GameData.PlayersNum, TEXT("The number of players must equal the sum of slime types"));

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
		//SetStartCountPawn(FGAIController);
		IsAIPawn(FGAIController);
	}

	OnChangedTypePawn.Broadcast(LevelSetting.CountTypePawn);
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
	GetWorldTimerManager().SetTimer(GameTimeHandle, this, &AFGGameModeBase::GameTimerUpdate, 1.0f, true);
	SetMatchState(EFGMatchState::InProgress);
}

void AFGGameModeBase::GameTimerUpdate()
{
	TimeCountDown = FMath::Clamp(--TimeCountDown, 0, LevelSetting.TimeGame);
	CheckTimeReHeling();

	if (CheckTimerCount() || CheckSickPawn())
	{
		GameOver();
	}
}

bool AFGGameModeBase::CheckTimerCount() const
{
	if (TimeCountDown == 0)
	{
		return true; 
	}
	else return false;
}

void AFGGameModeBase::CheckTimeReHeling()
{
	if (TimeCountDown <= 20 && !LevelSetting.ReHealing)
	{
		GetWorldTimerManager().SetTimer(ReHealingTimer, this, &AFGGameModeBase::ReHealingUpdate, 1.0f, false);
		LevelSetting.ReHealing = true;
		IsReHealing = true;
		OnReHealingPawn.Broadcast(LevelSetting.ReHealingPawn);
	}
}

void AFGGameModeBase::ReHealingUpdate() 
{
	LevelSetting.TimeReHealing = FMath::Clamp(--TimeReHealing, 0, LevelSetting.TimeReHealing);
	if (TimeReHealing == 0)
	{
		LevelSetting.ReHealing = false;
		TimeReHealing = LevelSetting.TimeReHealing;
		GetWorldTimerManager().ClearTimer(ReHealingTimer);
	}
}

//At game startup, subscribe to the artificial character's delegate on collision
void AFGGameModeBase::HealingOrInfaction(const bool& Health, const ETypePawn& TypePawn)
{
	if (Health) 
	{
		HealingPawn(TypePawn);
		SetPenalTime();
	}
	else 
	{
		InfactionPawn(TypePawn);
		CheckSickPawn();
	}

	OnChangedTypePawn.Broadcast(LevelSetting.CountTypePawn);
}

void AFGGameModeBase::SetPenalTime()
{
	if (IsReHealing) 
	{
		IsReHealing = false;
		return;
	}
	else 
	{
		if (TimeCountDown > 0) 
		{
			TimeCountDown = FMath::Clamp(TimeCountDown - GameData.PenalTime, 0, LevelSetting.TimeGame);

			if (CheckTimerCount())
			{
				GameOver();
			}
		}
	}
}

bool AFGGameModeBase::CheckSickPawn() const
{
	if (LevelSetting.CountTypePawn.CountSick == GameData.PlayersNum)
	{
		return true;
	}
	else return false;
}

void AFGGameModeBase::HealingPawn(const ETypePawn& PawnType)
{
	switch (PawnType)
	{
	case ETypePawn::Doctor:
	{
		LevelSetting.CountTypePawn.CountDoctor++;
		break;
	}
	case ETypePawn::Assistant:
	{
		LevelSetting.CountTypePawn.CountAssistent++;
		break;
	}
	case ETypePawn::Worker:
	{
		LevelSetting.CountTypePawn.CountWorker++;
		break;
	}
	}
	LevelSetting.CountTypePawn.CountSick--;
}

void AFGGameModeBase::InfactionPawn(const ETypePawn& PawnType)
{
	switch (PawnType)
	{
	case ETypePawn::Doctor:
	{
		LevelSetting.CountTypePawn.CountDoctor--;
		break;
	}
	case ETypePawn::Assistant:
	{
		LevelSetting.CountTypePawn.CountAssistent--;
		break;
	}
	case ETypePawn::Worker:
	{
		LevelSetting.CountTypePawn.CountWorker--;
		break;
	}
	}
	LevelSetting.CountTypePawn.CountSick++;
}

//Game Over
void AFGGameModeBase::GameOver()
{
	GetWorldTimerManager().ClearTimer(GameTimeHandle);
	GetWorldTimerManager().ClearTimer(ReHealingTimer);
	UE_LOG(LogFGGameModeBase, Warning, TEXT("====Game Over====="));

	for (auto Pawn : TActorRange<APawn>(GetWorld())) 
	{
		if (Pawn) 
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(EFGMatchState::GameOver);
}

//Set state to match
void AFGGameModeBase::SetMatchState(EFGMatchState State)
{
	if (MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}

bool AFGGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) 
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if (PauseSet) 
	{
		SetMatchState(EFGMatchState::Pause);
	}

	return PauseSet;
}

bool AFGGameModeBase::ClearPause() 
{
	const auto PausedClear = Super::ClearPause();
	if (PausedClear) 
	{
		SetMatchState(EFGMatchState::InProgress);
	}

	return PausedClear;
}