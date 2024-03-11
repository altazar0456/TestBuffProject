// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TBPAIController.generated.h"

UCLASS()
class TESTBUFFPROJECT_API ATBPAIController : public AAIController
{
    GENERATED_BODY()
    
protected:
    virtual void OnPossess(APawn* InPawn) override;
};
