// First Game

#include "AI/FGAICharacter.h"
#include "AI/FGAIController.h"
#include "Components/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/FGBaseCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "FGGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGAICharacter, All, All)

AFGAICharacter::AFGAICharacter() 
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AFGAIController::StaticClass();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AFGAICharacter::Hit);
}

void AFGAICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()) 
	{
		if (const auto GameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnReHealingPawn.AddUObject(this, &AFGAICharacter::OnTimerReHealing);
		}
	}
}

void AFGAICharacter::Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	if (const auto OverlapActor = Cast<AFGBaseCharacter>(OtherActor))
	{
		if (GetSettingPawn().HealthType == OverlapActor->GetSettingPawn().HealthType) return;

		UE_LOG(LogFGAICharacter, Display, TEXT("Overlap: %s"), *OverlapActor->GetName());
		CheckPawn(OverlapActor);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlapSound, GetActorLocation());
	}
}

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
}

void AFGAICharacter::Healing(AFGBaseCharacter* OtherPawn)
{
	if (OtherPawn->GetSettingPawn().TypePawn == ETypePawn::MainPawn) return;

	OtherPawn->HealthComponent->SetSettingsPawn(true);
	OtherPawn->SetColor(OtherPawn->HealthComponent->CheckColorPawn(OtherPawn->GetSettingPawn().TypePawn));
	OnHealthChanged.Broadcast(OtherPawn->HealthComponent->GetSettingsPawn().HealthType, OtherPawn->HealthComponent->GetSettingsPawn().TypePawn);
	SpawnNiagara(*OtherPawn, true);
}

void AFGAICharacter::Infaction()
{
	if (!HealthComponent->GetSettingsPawn().HealthType) return;

	HealthComponent->SetSettingsPawn(false);
	SetColor(HealthComponent->GetColorParam().Sick);
	OnHealthChanged.Broadcast(HealthComponent->GetSettingsPawn().HealthType, HealthComponent->GetSettingsPawn().TypePawn);
	SpawnNiagara(*this, false);
}

void AFGAICharacter::OnTimerReHealing(const ETypePawn& ReHealingPawn)
{
	if (ReHealingPawn == HealthComponent->GetSettingsPawn().TypePawn && !HealthComponent->GetSettingsPawn().HealthType)
	{
		UE_LOG(LogFGAICharacter, Display, TEXT("Healing"));
		Healing(this);
	}
}

UNiagaraComponent* AFGAICharacter::SpawnNiagara(const AFGBaseCharacter& SlimeMesh, const bool IsHelling)
{
	auto Effect = DefaultEffect;

	if (NiagaraEffects.Contains(IsHelling)) 
	{
		Effect = NiagaraEffects[IsHelling];
	}

	return UNiagaraFunctionLibrary::SpawnSystemAttached(Effect, SlimeMesh.GetMesh(), NiagaraSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}