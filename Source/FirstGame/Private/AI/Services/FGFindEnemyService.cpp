// First Game

#include "AI/Services/FGFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/FGAICharacter.h"
#include "Components/FGAIPerceptionComponent.h"

UFGFindEnemyService::UFGFindEnemyService() 
{
	NodeName = "Find Enemy";
}

void UFGFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard) 
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Controller->FindComponentByClass<UFGAIPerceptionComponent>();
		if (PerceptionComponent) 
		{
			if (const auto Pawn = Cast<AFGAICharacter>(PerceptionComponent->GetEnemy()))
			{
				Blackboard->SetValueAsBool(IsMainPawnKey.SelectedKeyName, false);
			}
			else 
			{
				Blackboard->SetValueAsBool(IsMainPawnKey.SelectedKeyName, true);
			}

			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}