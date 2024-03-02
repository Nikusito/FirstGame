// First Game

#pragma once

#include "CoreMinimal.h"
#include "Player/FGBaseCharacter.h"
#include "FGCoreTypes.h"
#include "FGAICharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, bool, ETypePawn);

class UBehaviorTree;

UCLASS()
class FIRSTGAME_API AFGAICharacter : public AFGBaseCharacter
{
	GENERATED_BODY()

public:
	AFGAICharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	FOnHealthChanged OnHealthChanged;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle;

	UFUNCTION()
	void Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void CheckPawn(AFGBaseCharacter* Pawn);
	void Healing(AFGBaseCharacter* OtherPawn);
	void Infaction();
};
