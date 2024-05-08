// First Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FGCoreTypes.h"
#include "FGMenuGameModeBase.generated.h"

UCLASS()
class FIRSTGAME_API AFGMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AFGMenuGameModeBase();

	FOnUIStateChangedSignature OnUIStateChanged;

	void SetUIState(EFGUIState State);

	virtual void StartPlay() override;
};
