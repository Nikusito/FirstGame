// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGDevActor.generated.h"

class UBoxComponent;

UCLASS()
class FIRSTGAME_API AFGDevActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFGDevActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Color = FLinearColor::Blue;

	FLinearColor GetColor() const { return Color; }

protected:
	virtual void BeginPlay() override;
	void SetColor(const FLinearColor& SetColor);
};
