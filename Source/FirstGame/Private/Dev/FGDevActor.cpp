// First Game

#include "Dev/FGDevActor.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

DEFINE_LOG_CATEGORY_STATIC(LogDevActor, All, All)

AFGDevActor::AFGDevActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	CollisionComponent = CreateDefaultSubobject <UBoxComponent>("BoxComponent");
	CollisionComponent->SetupAttachment(SceneComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(CollisionComponent);
}

void AFGDevActor::BeginPlay()
{
	Super::BeginPlay();

	SetColor(Color);
}

void AFGDevActor::SetColor(const FLinearColor& SetColor)
{
	UMaterialInstanceDynamic* DynMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial) 
	{
		DynMaterial->SetVectorParameterValue("Color", SetColor);
	}
}