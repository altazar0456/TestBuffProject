// Test Buff Project. All Rights Reserved.

#include "TBPBaseGameMode.h"
#include "Characters/TBPPlayerCharacter.h"
#include "UI/TBPGameHUD.h"

ATBPBaseGameMode::ATBPBaseGameMode()
{	
	DefaultPawnClass = ATBPPlayerCharacter::StaticClass();
	HUDClass = ATBPGameHUD::StaticClass();
}
