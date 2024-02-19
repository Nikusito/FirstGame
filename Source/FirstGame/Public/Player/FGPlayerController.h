// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FGPlayerController.generated.h"

class AFGPlayerCharacter;

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

	UPROPERTY()
	AFGPlayerCharacter* CurrentPawn;

	int32 CurrentPawnIndex = 0;

	void GetPawn();
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void AddControllerPitchInput(float Amount);
	void AddControllerYawInput(float Amount);
	void Jump();
};
