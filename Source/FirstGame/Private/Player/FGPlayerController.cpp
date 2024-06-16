// First Game

#include "Player/FGPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FGPlayerCharacter.h"
#include "FGGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogFGPlayerController, All, All)

void AFGPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	GetPawn();

	if (GetWorld())
	{
		if (const auto GameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AFGPlayerController::OnMatchStateChanged);
		}
	}
}

void AFGPlayerController::SetupInputComponent() 
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAxis("MoveForward", this, &AFGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFGPlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AFGPlayerController::AddControllerPitchInput);
	InputComponent->BindAxis("TurnAround", this, &AFGPlayerController::AddControllerYawInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFGPlayerController::Jump);
	InputComponent->BindAction("PauseGame", IE_Pressed, this, &AFGPlayerController::OnPauseGame);
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

void AFGPlayerController::OnPauseGame() 
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AFGPlayerController::OnMatchStateChanged(EFGMatchState State) 
{
	if (State == EFGMatchState::InProgress) 
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else 
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}