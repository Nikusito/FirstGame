// First Game

#pragma once

#include "CoreMinimal.h"
#include "Player/FGBaseCharacter.h"
#include "FGAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class FIRSTGAME_API AFGAICharacter : public AFGBaseCharacter
{
	GENERATED_BODY()

public:
	AFGAICharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle;

	/*UFUNCTION()
	void Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);*/

	UFUNCTION()
	void OverlapActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void CheckPawn(AFGBaseCharacter* Pawn);
	void Healing(AFGBaseCharacter* OtherPawn);
	void Infaction();

	void OnTimerClearMaterial(); //We'll have to delete it later
};
