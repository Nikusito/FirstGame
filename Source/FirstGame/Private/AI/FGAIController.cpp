// First Game

#include "AI/FGAIController.h"
#include "AI/FGAICharacter.h"

void AFGAIController::OnPossess(APawn* InPawn) 
{
	Super::OnPossess(InPawn);

	const auto FGAICharacter = Cast<AFGAICharacter>(InPawn);
	if (FGAICharacter)
	{
		RunBehaviorTree(FGAICharacter->BehaviorTreeAsset);
	}
}