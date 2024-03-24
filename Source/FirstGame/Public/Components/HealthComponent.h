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

	FSettingPawn GetSettingsPawn() const { return SettingPawn; }
	FLinearColor GetColorPawn() const { return SettingPawn.TypeColorPawn; }
	FTypeColor GetColorParam() const { return TypeColorsPawn; }

	void SetSettingsPawn(bool NewHealthPawn) { SettingPawn.HealthType = NewHealthPawn; }

	FLinearColor CheckColorPawn(const ETypePawn& PawnType);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FSettingPawn SettingPawn;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colors Pawn")
	FTypeColor TypeColorsPawn;

	virtual void BeginPlay() override;	

	void SetStartSettingsPawn();
};
