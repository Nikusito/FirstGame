// First Game

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FGAIController.generated.h"

UCLASS()
class FIRSTGAME_API AFGAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
