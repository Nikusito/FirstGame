#pragma once
#include "FGCoreTypes.generated.h"

//Pawn
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, const bool&, const ETypePawn&);

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

//Game Data
USTRUCT(BlueprintType)
struct FCountTypePawn
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountSick = 1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountDoctor = 0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountAssistent = 0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountWorker = 0;
};

//Game Data: GameMode
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedTypePawn, const FCountTypePawn&, CountSlime);

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FCountTypePawn CountTypePawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 PlayersNum = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "360"))
	int32 TimeGame = 10; //in seconds
};