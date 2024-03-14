// First Game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "FGCoreTypes.h"
#include "FGTypePawnDecorator.generated.h"

UCLASS()
class FIRSTGAME_API UFGTypePawnDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UFGTypePawnDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	ETypePawn TypePawn = ETypePawn::Doctor;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
