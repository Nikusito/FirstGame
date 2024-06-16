// First Game

#include "Components/HealthComponent.h"
#include "FGGameModeBase.h"
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
		SetBotsType();
	}
}

void UHealthComponent::SetBotsType() 
{
	if (!GetWorld()) return;

	const auto GameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	if(GameMode->CountType.CountDoctor != 0)
	{
		SettingPawn.HealthType = true;
		SettingPawn.TypePawn = ETypePawn::Doctor;
		SettingPawn.TypeColorPawn = CheckColorPawn(SettingPawn.TypePawn);
		GameMode->CountType.CountDoctor--;
	}
	else 
	{
		if (GameMode->CountType.CountAssistent != 0) 
		{
			SettingPawn.HealthType = true;
			SettingPawn.TypePawn = ETypePawn::Assistant;
			SettingPawn.TypeColorPawn = CheckColorPawn(SettingPawn.TypePawn);
			GameMode->CountType.CountAssistent--;
		}
		else 
		{
			SettingPawn.HealthType = true;
			SettingPawn.TypePawn = ETypePawn::Worker;
			SettingPawn.TypeColorPawn = CheckColorPawn(SettingPawn.TypePawn);
			GameMode->CountType.CountWorker--;
		}
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