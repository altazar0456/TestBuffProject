// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TBPBaseBuff.generated.h"

class ATBPBaseCharacter;

//TODO: forbid to use this class for designers
UCLASS()
class TESTBUFFPROJECT_API UTBPBaseBuff : public UObject
{
    GENERATED_BODY()
	
public:
	virtual void Apply(ATBPBaseCharacter* Target);
};
