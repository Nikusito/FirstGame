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

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jump")
	int32 StartJump = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump", meta = (ClampMin = "1.0", ClampMax = "5.0"))
	int32 CountJump = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Jump", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	float TimerRate = 2.0f;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	TArray<AActor*>Pawns;

	UPROPERTY()
	AFGBasePawn* CurrentPawn;

	int32 CurrentPawnIndex = 0;
	FTimerHandle TimerHandleJump;

	void GetPawn();
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void AddControllerPitchInput(float Amount);
	void AddControllerYawInput(float Amount);
	void Jump();
	void ResetJump();
};
