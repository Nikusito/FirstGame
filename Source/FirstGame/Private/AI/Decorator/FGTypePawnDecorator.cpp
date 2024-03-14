// First Game

#include "AI/Decorator/FGTypePawnDecorator.h"
#include "AIController.h"
#include "Components/HealthComponent.h"

UFGTypePawnDecorator::UFGTypePawnDecorator() 
{
	NodeName = "Type Pawn";
}

bool UFGTypePawnDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = Controller->GetPawn()->FindComponentByClass<UHealthComponent>();
	if (!HealthComponent || !HealthComponent->GetSettingsPawn().HealthType) return false;

	return HealthComponent->GetSettingsPawn().TypePawn == TypePawn;
}