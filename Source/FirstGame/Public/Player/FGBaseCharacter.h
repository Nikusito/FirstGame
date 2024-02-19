// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FGCoreTypes.h"
#include "FGBaseCharacter.generated.h"

class UHealthComponent;

UCLASS()
class FIRSTGAME_API AFGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFGBaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Material")
	FName MaterialColorName = "Color";

	FLinearColor GetColor() const;
	FSettingPawn GetSettingPawn() const;
	void SetColor(const FLinearColor& SetColor);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
