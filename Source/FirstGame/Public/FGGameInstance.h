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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	EFGDifficulty DifficultyLevel = EFGDifficulty::Simple;
};
