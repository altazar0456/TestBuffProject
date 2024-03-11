// Test Buff Project. All Rights Reserved.

#include "TBPAICharacter.h"
#include "TBPAIController.h"

ATBPAICharacter::ATBPAICharacter()
{
    AIControllerClass = ATBPAIController::StaticClass();
	
	bUseControllerRotationYaw = false;
}
