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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountDoctor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountAssistent = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CountTypePawn")
	int32 CountWorker = 0;
};

//Level dificulty
UENUM(BlueprintType)
enum class EFGDifficulty : uint8
{
	Simple = 0,
	Middle,
	Hard
};

//Customizing the level by difficulty
USTRUCT(BlueprintType)
struct FLevelSetting
{
	GENERATED_USTRUCT_BODY()

	//in seconds
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelSetting", meta = (ClampMin = "1", ClampMax = "360"))
	int32 TimeGame = 10; 

	//Flag for healing through time
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	bool ReHealing = false;

	//Type of pawn for healing
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	ETypePawn ReHealingPawn = ETypePawn::Worker;

	//in seconds
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "20", ClampMax = "50"))
	int32 TimeReHealing = 20;

	//The number of players must equal the sum of slime types
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FCountTypePawn CountTypePawn;
};

//Game Data: GameMode
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedTypePawn, const FCountTypePawn&, CountSlime);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnReHealingPawnSignature, const ETypePawn&);

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelSetting")
	TMap<EFGDifficulty, FLevelSetting> LevelsSetting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 PlayersNum = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "20"))
	int32 PenalTime = 5; //in seconds
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EFGMatchState);

UENUM (BlueprintType)
enum class EFGMatchState : uint8
{
	WaitingToStatrt = 0,
	InProgress,
	Pause,
	GameOver
};

//UI
USTRUCT(BlueprintType)
struct FLevelUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FName LevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FName LevelDisplayName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* LevelThumb;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* LevelBackground;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelUIData&);

UENUM(BlueprintType)
enum class EFGUIState : uint8
{
	StartMenu = 0,
	LevelsSelector,
	HelpAndSetting,
	Back
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUIStateChangedSignature, EFGUIState);