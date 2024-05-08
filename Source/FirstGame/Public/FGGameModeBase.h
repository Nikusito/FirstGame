// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FGCoreTypes.h"
#include "FGGameModeBase.generated.h"

class AAIController;

UCLASS()
class FIRSTGAME_API AFGGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
	AFGGameModeBase();

	FCountTypePawn CountType;

	UPROPERTY(BlueprintAssignable)
	FOnChangedTypePawn OnChangedTypePawn;

	FOnReHealingPawnSignature OnReHealingPawn;

	FOnMatchStateChangedSignature OnMatchStateChanged;

	FGameData GetGameData() const { return GameData; }
	int32 GetTimeSeconds() const { return TimeCountDown; }
	FLevelSetting GetLevelSetting() const { return LevelSetting; }
	
	bool CheckSickPawn() const;

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FGameData GameData;

private:
	FLevelSetting LevelSetting;
	EFGMatchState MatchState = EFGMatchState::WaitingToStatrt;
	int32 TimeCountDown = 0;
	int32 TimeReHealing = 0;
	FTimerHandle GameTimeHandle;
	FTimerHandle ReHealingTimer;
	bool NewSpawn = false;
	bool IsReHealing = false;

	UFUNCTION()
	void HealingOrInfaction(const bool& Health, const ETypePawn& TypePawn);

	void HealingPawn(const ETypePawn& PawnType);
	void InfactionPawn(const ETypePawn& PawnType);
	void IsAIPawn(AAIController* InConroller);
	void SpawnBots();
	void StartGame();
	void GameTimerUpdate();
	void ReHealingUpdate();
	void SetPenalTime();
	void SetLevelSetting();
	void CheckTimeReHeling();

	bool CheckTimerCount() const;

	void SetMatchState(EFGMatchState State);

	void GameOver();
};
