// First Game

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FGCoreTypes.h"
#include "FGGameInstance.generated.h"

UCLASS()
class FIRSTGAME_API UFGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FLevelUIData GetStartupLevel() const { return StartupLevel; }
	void SetStartupLevel(const FLevelUIData& Data) { StartupLevel = Data; }

	TArray<FLevelUIData> GetLevelsData() const { return LevelsData; }

	FName GetMenuLevelName() const { return MenuLevelName; }

	EFGDifficulty GetDifficultyLevel() const { return DifficultyLevel; }
	void SetDifficultyLevel(const EFGDifficulty& Difficulty) { DifficultyLevel = Difficulty; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TArray<FLevelUIData> LevelsUIData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FName MenuLevelName = NAME_None;

private:
	EFGDifficulty DifficultyLevel = EFGDifficulty::Simple;
	FLevelUIData StartupLevel;
	const TArray<FLevelUIData>& LevelsData = LevelsUIData;
};
