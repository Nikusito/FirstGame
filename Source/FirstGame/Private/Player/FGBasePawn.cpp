// First Game

#include "Player/FGBasePawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

	CollisionComponent = CreateDefaultSubobject <USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(45.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->SetupAttachment(StaticMesh);

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
	
}

void AFGBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFGBasePawn::MoveForward(float Amount) 
{
	if (Amount == 0.0f)return;
	MoveSetting.VectorForce = GetActorForwardVector() * MoveSetting.MovementForce * Amount;
	StaticMesh->AddForce(MoveSetting.VectorForce);
}

void AFGBasePawn::MoveRight(float Amount) 
{
	if (Amount == 0.0f)return;
	MoveSetting.VectorForce = GetActorRightVector() * MoveSetting.MovementForce * Amount;
	StaticMesh->AddForce(MoveSetting.VectorForce);
}

void AFGBasePawn::Jump() 
{
	MoveSetting.VectorForce = GetActorUpVector() * MoveSetting.JumpImpuls;
	StaticMesh->AddImpulse(MoveSetting.VectorForce);
}

/*void AFGBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}*/