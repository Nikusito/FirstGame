// First Game

#include "Player/FGBasePawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Dev/FGDevActor.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePawn, All, All)

AFGBasePawn::AFGBasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetSimulatePhysics(true);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(StaticMesh);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void AFGBasePawn::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);

	SetSettingsPawn();
	SetColor(SettingsPawn.TypeColorPawn);

	StaticMesh->OnComponentHit.AddDynamic(this, &AFGBasePawn::Hit);
}

void AFGBasePawn::Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (const auto DevActor = Cast<AFGDevActor>(OtherActor)) 
	{
		UE_LOG(LogBasePawn, Warning, TEXT("Overlap: %s"), *DevActor->GetName());
		if (DevActor->GetColor() == SettingsPawn.TypeColorPawn) return;

		SetColor(DevActor->GetColor());
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AFGBasePawn::OnTimerClearMaterial, Setting.TimerRate, false);
	}
}

void AFGBasePawn::SetColor(const FLinearColor& SetColor) 
{
	UMaterialInstanceDynamic* DynMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", SetColor);
	}
}

void AFGBasePawn::SetSettingsPawn()
{
	SettingsPawn = HealthComponent->GetSettingsPawn();
}

void AFGBasePawn::OnTimerClearMaterial()
{
	UE_LOG(LogBasePawn, Warning, TEXT("Clear Material"));
	SetColor(SettingsPawn.TypeColorPawn = HealthComponent->GetColorPawn());
}

void AFGBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFGBasePawn::MoveForward(float Amount) 
{
	if (Amount == 0.0f)return;
	Setting.VectorForce = GetActorForwardVector() * Setting.MovementForce * Amount;
	StaticMesh->AddForce(Setting.VectorForce);
}

void AFGBasePawn::MoveRight(float Amount) 
{
	if (Amount == 0.0f)return;
	Setting.VectorForce = GetActorRightVector() * Setting.MovementForce * Amount;
	StaticMesh->AddForce(Setting.VectorForce);
}

void AFGBasePawn::Jump() 
{
	Setting.VectorForce = GetActorUpVector() * Setting.JumpImpuls;
	StaticMesh->AddImpulse(Setting.VectorForce);
}