// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TBPBuffSystem.h"
#include "UObject/Object.h"
#include "TBPBaseBuff.generated.h"

class ATBPBaseCharacter;
class UNiagaraSystem;

//TODO: forbid to use this class for designers
UCLASS()
class TESTBUFFPROJECT_API UTBPBaseBuff : public UObject
{
    GENERATED_BODY()
	
public:
	bool IsInstanced() const { return bInstanced; }
	
	virtual void Activate(ATBPBaseCharacter* Target) {}
	virtual void TickBuff(ATBPBaseCharacter* Target, float DeltaTime) {}
	virtual void OnEndBuff(ATBPBaseCharacter* Target, bool bIsInterrupted) {}
	
	// Is it instant Buff or does it need time to execute
	virtual bool IsInstant() const { return true; }
	virtual float GetDuration() const { return 0.0f; }
	virtual float GetTickPeriod() const { return 0.1f; }

	const FGameplayTag& GetGameplayTag() const { return BuffTag; }
	
	virtual void SetParameters(const FTBPBuffSettings& BuffSettings) {}
	
protected:	
	UPROPERTY(EditAnywhere, Category = "Buff")
	FGameplayTag BuffTag;
	
	// In case buff need to store runtime data in properties need to set it true  
	UPROPERTY(VisibleAnywhere, Category = "Advanced")
	bool bInstanced = false;
};

//TODO: forbid to use this class for designers
UCLASS()
class TESTBUFFPROJECT_API UTBPLastingBuff : public UTBPBaseBuff
{
	GENERATED_BODY()
	
public:
	
	virtual void Activate(ATBPBaseCharacter* Target) override;
	virtual void OnEndBuff(ATBPBaseCharacter* Target, bool bIsInterrupted) override;
	
	virtual bool IsInstant() const override { return false; }
	virtual float GetDuration() const override { return Duration; }
	virtual float GetTickPeriod() const override { return TickDeltaTime; }

	virtual void SetParameters(const FTBPBuffSettings& BuffSettings) override;
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Buff", meta = (ClampMin = "0.0001", ClampMax = "1000.0"))
	float Duration = 3.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Buff", meta = (ClampMin = "0.0001", ClampMax = "1000.0"))
	float TickDeltaTime = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UNiagaraSystem* BuffVFX = nullptr;	
};