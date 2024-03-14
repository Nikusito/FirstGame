// First Game

#include "AI/FGAIController.h"
#include "AI/FGAICharacter.h"
#include "Components/FGAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGAIController, All, All)

AFGAIController::AFGAIController() 
{
	FGAIPerceptionComponent = CreateDefaultSubobject<UFGAIPerceptionComponent>("FGPerceptionComponent");
	SetPerceptionComponent(*FGAIPerceptionComponent);
}

void AFGAIController::OnPossess(APawn* InPawn) 
{
	Super::OnPossess(InPawn);

	const auto FGAICharacter = Cast<AFGAICharacter>(InPawn);
	if (FGAICharacter)
	{
		RunBehaviorTree(FGAICharacter->BehaviorTreeAsset);
	}
}

void AFGAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	const auto AimActor = GetFocusActor();
	SetFocus(AimActor);
}

AActor* AFGAIController::GetFocusActor()const 
{
	if (!GetBlackboardComponent()) return nullptr;

	if (!GetBlackboardComponent()->GetValueAsBool(IsMainPawnKeyName)) 
	{
		return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
	}

	return nullptr;
}