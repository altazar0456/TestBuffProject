﻿// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TBPBaseBuff.generated.h"

class ATBPBaseCharacter;

//TODO: Implement instanced behaviour where each Buff can have their own runtime memory if we need it
//TODO: forbid to use this class for designers
UCLASS()
class TESTBUFFPROJECT_API UTBPBaseBuff : public UObject
{
    GENERATED_BODY()
	
public:
	virtual void Activate(ATBPBaseCharacter* Target) const {}
	virtual void TickBuff(ATBPBaseCharacter* Target, float DeltaTime) const {}
	virtual void OnEndBuff(ATBPBaseCharacter* Target) const {}

	//TODO: maybe move to properties or move to properties for derived durable class
	// Is it instant Buff or does it need time to execute
	virtual bool IsInstant() const { return true; }
	virtual float GetDuration() const { return 0.0f; }
	virtual float GetTickPeriod() const { return 0.1f; }
	
protected:	
	// TODO: implement instanced behaviour if we need it
	// In case buff need to store runtime data in properties need to set it true  
	// UPROPERTY(VisibleAnywhere, Category = "Advanced")
	// bool bInstanced = false;
};

//TODO: forbid to use this class for designers
UCLASS()
class TESTBUFFPROJECT_API UTBPLastingBuff : public UTBPBaseBuff
{
	GENERATED_BODY()
	
	virtual bool IsInstant() const override { return false; }
	virtual float GetDuration() const override { return Duration; }
	virtual float GetTickPeriod() const override { return TickDeltaTime; }
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Buff", meta = (ClampMin = "0.0001", ClampMax = "1000.0"))
	float Duration = 3.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Buff", meta = (ClampMin = "0.0001", ClampMax = "1000.0"))
	float TickDeltaTime = 1.0f;
};