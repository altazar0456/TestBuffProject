// Test Buff Project. All Rights Reserved.

#include "TBPAIController.h"
#include "TBPAICharacter.h"

void ATBPAIController::OnPossess(APawn* InPawn)
{	
	Super::OnPossess(InPawn);

	if (const auto STUCharacter = Cast<ATBPAICharacter>(InPawn))
	{
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}
}
