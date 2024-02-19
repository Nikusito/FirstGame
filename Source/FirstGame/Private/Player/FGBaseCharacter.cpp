// First Game

#include "Player/FGBaseCharacter.h"
#include "Components/HealthComponent.h"

AFGBaseCharacter::AFGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void AFGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);

	SetColor(HealthComponent->GetColorPawn());
}

void AFGBaseCharacter::SetColor(const FLinearColor& SetColor)
{
	UMaterialInstanceDynamic* DynMaterial = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue(MaterialColorName, SetColor);
	}
}

FLinearColor AFGBaseCharacter::GetColor() const
{
	return HealthComponent->GetColorPawn();
}

FSettingPawn AFGBaseCharacter::GetSettingPawn() const
{
	return HealthComponent->GetSettingsPawn();
}

void AFGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

