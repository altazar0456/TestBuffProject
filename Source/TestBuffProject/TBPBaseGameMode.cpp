// Test Buff Project. All Rights Reserved.

#include "TBPBaseGameMode.h"
#include "Player/TBPPlayerCharacter.h"
#include "UI/TBPGameHUD.h"

ATBPBaseGameMode::ATBPBaseGameMode()
{	
	DefaultPawnClass = ATBPPlayerCharacter::StaticClass();
	HUDClass = ATBPGameHUD::StaticClass();
}

void ATBPBaseGameMode::StartPlay()
{
	Super::StartPlay();

	check(BuffSettings);	
}