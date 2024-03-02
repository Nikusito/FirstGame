// First Game

#include "UI/FGPlayerWidget.h"
#include "Player/FGBaseCharacter.h"
#include "Components/HealthComponent.h"
#include "FGGameModeBase.h"
#include "FGCoreTypes.h"
#include "Kismet/GameplayStatics.h"

//Sign up for a GameMode delegate at game startup

FCountTypePawn UFGPlayerWidget::GetStartGameCountPawn()
{
	const auto GameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode());

	TArray<AActor*>Pawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFGBaseCharacter::StaticClass(), Pawns);

	if (Pawns.Num() <= 1) return GameMode->GetCountPawn();

	for (const auto Slime : Pawns)
	{
		const auto Player = Cast<AFGBaseCharacter>(Slime);
		if (!Player) continue;

		const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
		const auto HealthComponent = Cast<UHealthComponent>(Component);
		if (!HealthComponent)continue;

		GameMode->SetStartCountPawn(HealthComponent->GetSettingsPawn().TypePawn, HealthComponent->GetSettingsPawn().HealthType);
	}

	return GameMode->GetCountPawn();
}