// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FGCoreTypes.h"
#include "FGGameModeBase.generated.h"


UCLASS()
class FIRSTGAME_API AFGGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
	AFGGameModeBase();

	FCountTypePawn GetCountPawn() const { return CountPawns; }

	void SetStartCountPawn(const ETypePawn& PawnType, const bool Health);
	void HealingPawn(const ETypePawn& PawnType);
	void InfactionPawn(const ETypePawn& PawnType);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FCountTypePawn CountPawns;
};
