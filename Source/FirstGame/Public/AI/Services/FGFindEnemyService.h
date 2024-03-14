// First Game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FGFindEnemyService.generated.h"

UCLASS()
class FIRSTGAME_API UFGFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UFGFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector EnemyActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector IsMainPawnKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
