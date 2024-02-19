// First Game

#include "AI/FGAICharacter.h"
#include "AI/FGAIController.h"
#include "Components/HealthComponent.h"
#include "TimerManager.h"
#include "Player/FGBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGAICharacter, All, All)

AFGAICharacter::AFGAICharacter() 
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AFGAIController::StaticClass();
}

void AFGAICharacter::BeginPlay()
{
	Super::BeginPlay();

	//CollisionBox->OnComponentHit.AddDynamic(this, &AFGAIPawn::Hit);
	//CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFGAIPawn::OverlapActor);
}

void AFGAICharacter::OverlapActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetWorld()) return;

	const auto OverlapActor = Cast<AFGBaseCharacter>(OtherActor);

	if (OverlapActor)
	{
		if (GetSettingPawn().HealthType == OverlapActor->GetSettingPawn().HealthType) return;

		//UE_LOG(LogFGAICharacter, Warning, TEXT("Overlap: %s"), *OverlapActor->GetName());
		CheckPawn(OverlapActor);
	}
}

//void AFGAICharacter::Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	if (!GetWorld()) return;
//
//	const auto OverlapActor = Cast<AFGBasePawn>(OtherActor);
//
//	if (OverlapActor)
//	{
//		if (GetSettingPawn().HealthType == OverlapActor->GetSettingPawn().HealthType) return;
//
//		UE_LOG(LogFGAICharacter, Warning, TEXT("Overlap: %s"), *OverlapActor->GetName());
//		CheckPawn(OverlapActor);
//	}
//}

void AFGAICharacter::CheckPawn(AFGBaseCharacter* Pawn)
{
	if (!Pawn->GetSettingPawn().HealthType && (Pawn->GetSettingPawn().TypePawn != ETypePawn::MainPawn))
	{
		switch (GetSettingPawn().TypePawn)
		{
		case ETypePawn::Doctor:
		{
			Healing(Pawn);
			break;
		}
		case ETypePawn::Assistant:
		{
			if (FMath::RandBool())
			{
				Healing(Pawn);
			}
			else
			{
				Infaction();
			}
			break;
		}
		case ETypePawn::Worker:
		{
			Infaction();
			break;
		}
		}
	}
	else
	{
		Infaction();
	}
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &AFGAIPawn::OnTimerClearMaterial, Setting.TimerRate, false);
}

void AFGAICharacter::Healing(AFGBaseCharacter* OtherPawn)
{
	if (OtherPawn->GetSettingPawn().TypePawn == ETypePawn::MainPawn) return;

	OtherPawn->HealthComponent->SettingPawn.HealthType = true;
	OtherPawn->SetColor(OtherPawn->HealthComponent->CheckColorPawn(OtherPawn->GetSettingPawn().TypePawn));
}

void AFGAICharacter::Infaction()
{
	HealthComponent->SettingPawn.HealthType = false;
	SetColor(HealthComponent->GetColorParam().Sick);
}

void AFGAICharacter::OnTimerClearMaterial()
{
	UE_LOG(LogFGAICharacter, Warning, TEXT("Clear Material"));
	HealthComponent->SettingPawn.HealthType = true;
	SetColor(HealthComponent->CheckColorPawn(GetSettingPawn().TypePawn));
}