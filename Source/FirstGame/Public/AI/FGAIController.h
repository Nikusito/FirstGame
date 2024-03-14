// First Game

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FGAIController.generated.h"

class UFGAIPerceptionComponent;

UCLASS()
class FIRSTGAME_API AFGAIController : public AAIController
{
	GENERATED_BODY()

public: 
	AFGAIController();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UFGAIPerceptionComponent* FGAIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FName FocusOnKeyName = "EnemyActor";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FName IsMainPawnKeyName = "IsMainPawn";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusActor()const;
};
