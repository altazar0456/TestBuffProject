// Test Buff Project. All Rights Reserved.

#include "TBPBaseGameMode.h"

#include "Buff/TBPBuffSystem.h"
#include "Player/TBPPlayerCharacter.h"
#include "UI/TBPGameHUD.h"

ATBPBaseGameMode::ATBPBaseGameMode()
{	
	DefaultPawnClass = ATBPPlayerCharacter::StaticClass();
	HUDClass = ATBPGameHUD::StaticClass();
	BuffSystem = CreateDefaultSubobject<UTBPBuffSystem>(TEXT("BuffSystem"));
}

void ATBPBaseGameMode::StartPlay()
{
	Super::StartPlay();

	check(BuffSystem);
	BuffSystem->OnStartPlay();
}