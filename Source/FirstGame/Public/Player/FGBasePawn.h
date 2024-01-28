// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FGCoreTypes.h"
#include "FGBasePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;

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
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move Setting")
	FMove Setting;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default Setting")
	FSettingPawn SettingsPawn;

	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void Jump();

	FLinearColor GetColor() const { return SettingsPawn.TypeColorPawn; }

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle;

	UFUNCTION()
	void Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void SetSettingsPawn();
	void SetColor(const FLinearColor& SetColor);

	void OnTimerClearMaterial(); //We'll have to delete it later
};
