// First Game

#include "Components/FGAIPerceptionComponent.h"
#include "AI/FGAIController.h"
#include "Player/FGPlayerController.h"
#include "Components/HealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UFGAIPerceptionComponent::GetEnemy() const 
{
	//Fill the array of characters seen with slime

	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	const auto PawnHealthComponent = Pawn->FindComponentByClass<UHealthComponent>();
	if (PawnHealthComponent && !PawnHealthComponent->GetSettingsPawn().HealthType) return nullptr;

	//Determining which controller the mucus belongs to and whether it is diseased
	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor : PercieveActors) 
	{
		const auto HealthComponent = PercieveActor->FindComponentByClass<UHealthComponent>();
		if (HealthComponent && !HealthComponent->GetSettingsPawn().HealthType) 
		{
			if (HealthComponent->GetSettingsPawn().TypePawn == ETypePawn::MainPawn) 
			{
				return BestPawn = PercieveActor;
				break;
			}
			else 
			{
				const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
				if (CurrentDistance < BestDistance) 
				{
					BestDistance = CurrentDistance;
					BestPawn = PercieveActor;
				}
			}
		}
	}

	return BestPawn;
}