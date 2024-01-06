// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FGBasePawn.generated.h"

class UCameraComponent;
class UFloatingPawnMovement;
class USpringArmComponent;

USTRUCT(BlueprintType)
struct FMove 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector VectorForce = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementForce = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	float JumpImpuls = 10000.0f;
};

UCLASS()
class FIRSTGAME_API AFGBasePawn : public APawn
{
	GENERATED_BODY()

public:
	AFGBasePawn();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move Setting")
	FMove MoveSetting;

protected:

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void Jump();
};
