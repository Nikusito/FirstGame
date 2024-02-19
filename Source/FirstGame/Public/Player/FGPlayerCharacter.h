// First Game

#pragma once

#include "CoreMinimal.h"
#include "Player/FGBaseCharacter.h"
#include "FGPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class FIRSTGAME_API AFGPlayerCharacter : public AFGBaseCharacter
{
	GENERATED_BODY()

public:
	AFGPlayerCharacter();

	void MoveForward(float Amount);
	void MoveRight(float Amount);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* SpringArmComponent;
};
