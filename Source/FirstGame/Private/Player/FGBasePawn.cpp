// First Game

#include "Player/FGBasePawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
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

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(StaticMesh);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AFGBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFGBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFGBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFGBasePawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFGBasePawn::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AFGBasePawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AFGBasePawn::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFGBasePawn::Jump);
}

void AFGBasePawn::MoveForward(float Amount) 
{
	MoveSetting.VectorForce = GetActorForwardVector() * MoveSetting.MovementForce * Amount;
	StaticMesh->AddForce(MoveSetting.VectorForce);
}

void AFGBasePawn::MoveRight(float Amount) 
{
	MoveSetting.VectorForce = GetActorRightVector() * MoveSetting.MovementForce * Amount;
	StaticMesh->AddForce(MoveSetting.VectorForce);
}

void AFGBasePawn::Jump() 
{
	MoveSetting.VectorForce = GetActorUpVector() * MoveSetting.JumpImpuls;
	StaticMesh->AddImpulse(MoveSetting.VectorForce);
}