// First Game

#include "Player/FGPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FGPlayerCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGPlayerController, All, All)

void AFGPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	GetPawn();
}

void AFGPlayerController::SetupInputComponent() 
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AFGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFGPlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AFGPlayerController::AddControllerPitchInput);
	InputComponent->BindAxis("TurnAround", this, &AFGPlayerController::AddControllerYawInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFGPlayerController::Jump);
}

void AFGPlayerController::GetPawn()
{
	if (!GetWorld()) return;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFGPlayerCharacter::StaticClass(), Pawns);
	if (Pawns.Num() < 1) return;

	CurrentPawn = Cast<AFGPlayerCharacter>(Pawns[CurrentPawnIndex]);
	if (!CurrentPawn) return;

	Possess(CurrentPawn);
}

void AFGPlayerController::MoveForward(float Amount)
{
	CurrentPawn->MoveForward(Amount);
}

void AFGPlayerController::MoveRight(float Amount)
{
	CurrentPawn->MoveRight(Amount);
}

void AFGPlayerController::AddControllerPitchInput(float Amount) 
{
	CurrentPawn->AddControllerPitchInput(Amount);
}

void AFGPlayerController::AddControllerYawInput(float Amount) 
{
	CurrentPawn->AddControllerYawInput(Amount);
}

void AFGPlayerController::Jump() 
{
	CurrentPawn->Jump();
}