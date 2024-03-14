// First Game

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "FGAIPerceptionComponent.generated.h"

UCLASS()
class FIRSTGAME_API UFGAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	AActor* GetEnemy() const;
};
