// Test Buff Project. All Rights Reserved.

#include "TBPAICharacter.h"
#include "TBPAIController.h"

ATBPAICharacter::ATBPAICharacter(const FObjectInitializer& ObjInit)  : Super(ObjInit)
{
    AIControllerClass = ATBPAIController::StaticClass();
	
	bUseControllerRotationYaw = false;
}
