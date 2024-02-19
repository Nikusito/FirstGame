// First Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGCoreTypes.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FSettingPawn SettingPawn;

	FSettingPawn GetSettingsPawn() const { return SettingPawn; }
	FLinearColor GetColorPawn() const { return SettingPawn.TypeColorPawn; }
	FTypeColor GetColorParam() const { return TypeColorsPawn; }

	FLinearColor CheckColorPawn(const ETypePawn& PawnType);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colors Pawn")
	FTypeColor TypeColorsPawn;

	virtual void BeginPlay() override;	

	void SetStartSettingsPawn();
};
