// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FGBasePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class USphereComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move Setting")
	FMove MoveSetting;

	virtual void Tick(float DeltaTime) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void Jump();

protected:
	virtual void BeginPlay() override;
};
