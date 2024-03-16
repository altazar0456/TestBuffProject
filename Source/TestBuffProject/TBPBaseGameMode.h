// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TBPBaseGameMode.generated.h"

class UTBPBuffSystem;

UCLASS()
class TESTBUFFPROJECT_API ATBPBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATBPBaseGameMode();
	virtual void StartPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Buff", meta = (EditInline))
	UTBPBuffSystem* BuffSystem = nullptr;
};



