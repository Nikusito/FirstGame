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
	UPROPERTY(BlueprintAssignable)
	FOnChangedTypePawn OnChangedTypePawn;

	AFGGameModeBase();

	FGameData GetGameData() const { return GameData; }
	int32 GetTimeSeconds() const { return TimeCountDown; }

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FGameData GameData;

private:
	int32 TimeCountDown = 0;
	FTimerHandle GameTimeHandle;

	UFUNCTION()
	void HealingOrInfaction(const bool& Health, const ETypePawn& TypePawn);

	void SetStartCountPawn(const AAIController* ControllerPawn);
	void HealingPawn(const ETypePawn& PawnType);
	void InfactionPawn(const ETypePawn& PawnType);
	void IsAIPawn(AAIController* InConroller);
	void SpawnBots();
	void StartGame();
	void GameTimerUpdate();
};
