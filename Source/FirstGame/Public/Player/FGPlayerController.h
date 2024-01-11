// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FGPlayerController.generated.h"

class AFGBasePawn;

UCLASS()
class FIRSTGAME_API AFGPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	TArray<AActor*>Pawns;

	int32 CurrentPawnIndex = 0;

	UPROPERTY()
	AFGBasePawn* CurrentPawn;

	void GetPawn();
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void AddControllerPitchInput(float Amount);
	void AddControllerYawInput(float Amount);
	void Jump();
};
