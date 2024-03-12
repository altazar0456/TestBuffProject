// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/TBPBaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TBPAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class TESTBUFFPROJECT_API ATBPAICharacter : public ATBPBaseCharacter
{
    GENERATED_BODY()
	
public:
    ATBPAICharacter(const FObjectInitializer& ObjInit);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
};
