#pragma once
#include "FGCoreTypes.generated.h"

//Pawn
UENUM(BlueprintType)
enum class ETypePawn : uint8
{
	MainPawn,
	Doctor,
	Assistant,
	Worker
};

USTRUCT(BlueprintType)
struct FTypeColor
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Sick = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Doctor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Assistant = FLinearColor::Yellow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Worker = FLinearColor::Gray;
};

//Pawn Settings
USTRUCT(BlueprintType)
struct FSettingPawn
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TypePawn")
	ETypePawn TypePawn = ETypePawn::MainPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TypeColorPawn")
	FLinearColor TypeColorPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool HealthType = false;
};

//UI
USTRUCT(BlueprintType)
struct FCountTypePawn
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountSick = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountDoctor = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountAssistent = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountWorker = 0;
};