// First Game

#include "Components/HealthComponent.h"
#include "Player/FGBaseCharacter.h"
#include "Player/FGPlayerController.h"
#include "FGCoreTypes.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();	

	SetStartSettingsPawn();
}

void UHealthComponent::SetStartSettingsPawn()
{
	auto Pawn = GetOwner();
	if (!Cast<AFGBaseCharacter>(Pawn)) return;
	
	if (const auto Controller = Pawn->GetInstigatorController<AFGPlayerController>()) 
	{
		SettingPawn.HealthType = false;
		SettingPawn.TypePawn = ETypePawn::MainPawn;
		SettingPawn.TypeColorPawn = CheckColorPawn(SettingPawn.TypePawn);
	}
	else 
	{
		SettingPawn.HealthType = true;
		SettingPawn.TypePawn = FMath::RandBool() ? ETypePawn::Doctor : FMath::RandBool() ? ETypePawn::Assistant : ETypePawn::Worker;
		SettingPawn.TypeColorPawn = CheckColorPawn(SettingPawn.TypePawn);

		/*FString TypePawn = FString(ETypePawn::Doctor == SettingPawn.TypePawn ? "Doctor" : ETypePawn::Assistant == SettingPawn.TypePawn ? "Assistant" : "Worker");
		UE_LOG(LogHealthComponent, Warning, TEXT("Not Player Pawn: %s"), *TypePawn);*/
	}
}

FLinearColor UHealthComponent::CheckColorPawn(const ETypePawn& PawnType)
{
	switch (PawnType)
	{
	case ETypePawn::Doctor: 
	{
		SettingPawn.TypeColorPawn = TypeColorsPawn.Doctor;
		break;
	}
	case ETypePawn::Assistant:
	{
		SettingPawn.TypeColorPawn = TypeColorsPawn.Assistant;
		break;
	}
	case ETypePawn::Worker:
	{
		SettingPawn.TypeColorPawn = TypeColorsPawn.Worker;
		break;
	}
	default: SettingPawn.TypeColorPawn = TypeColorsPawn.Sick;
		break;
	}

	return SettingPawn.TypeColorPawn;
}