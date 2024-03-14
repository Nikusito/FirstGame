// First Game

#pragma once

#include "CoreMinimal.h"
#include "Player/FGBaseCharacter.h"
#include "FGCoreTypes.h"
#include "FGAICharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, bool, ETypePawn);

class UBehaviorTree;
class UNiagaraSystem;
class UNiagaraComponent;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Slime")
	FName NiagaraSocketName = "NiagaraSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* DefaultEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<bool, UNiagaraSystem*> NiagaraEffects;

	virtual void BeginPlay() override;

	UNiagaraComponent* SpawnNiagara(const AFGBaseCharacter& SlimeMesh, const bool IsHelling);

private:
	FTimerHandle TimerHandle;

	UFUNCTION()
	void Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void CheckPawn(AFGBaseCharacter* Pawn);
	void Healing(AFGBaseCharacter* OtherPawn);
	void Infaction();
};
