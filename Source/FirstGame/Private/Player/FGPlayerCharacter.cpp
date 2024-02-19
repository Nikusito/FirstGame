// First Game

#include "Player/FGPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AFGPlayerCharacter::AFGPlayerCharacter() 
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetMesh());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AFGPlayerCharacter::MoveForward(float Amount)
{
	if (Amount == 0.0f)return;

	AddMovementInput(GetActorForwardVector(), Amount);
}

void AFGPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f)return;

	AddMovementInput(GetActorRightVector(), Amount);
}