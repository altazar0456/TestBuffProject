// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TBPBuffSystemComponent.generated.h"

class UTBPBaseBuff;

UCLASS()
class TESTBUFFPROJECT_API UTBPBuffSystemComponent : public UActorComponent
{
    GENERATED_BODY()
	
public:
	UTBPBuffSystemComponent();

	void ApplyBuff(UTBPBaseBuff* Buff);
};
