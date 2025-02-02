﻿// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TBPBaseBuff.h"
#include "TBPDamageBuff.generated.h"

UCLASS()
class TESTBUFFPROJECT_API UTBPDamageBuff : public UTBPBaseBuff
{
	GENERATED_BODY()
public:
	UTBPDamageBuff();
	virtual void Activate(ATBPBaseCharacter* Target) override;

	virtual void SetParameters(const FTBPBuffSettings& BuffSettings) override;
	
protected:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float Damage = 20.0f;
};
