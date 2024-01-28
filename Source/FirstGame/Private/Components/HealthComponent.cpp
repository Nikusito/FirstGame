// First Game

#include "Components/HealthComponent.h"
#include "Player/FGBasePawn.h"
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

	SetSettingsPawn();
}

void UHealthComponent::SetSettingsPawn()
{
	auto Pawn = GetOwner();
	if (!Cast<AFGBasePawn>(Pawn)) return;
	
	
	if (const auto Controller = Pawn->GetInstigatorController<AFGPlayerController>()) 
	{
		SettingPawn.HealthType = false;
		SettingPawn.TypePawn = ETypePawn::MainPawn;
		SettingPawn.TypeColorPawn = TypeColorsPawn.Sick;
	}
	else 
	{
		UE_LOG(LogHealthComponent, Warning, TEXT("Not Player Pawn"));
	}
}