// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TBPBaseBuff.h"
#include "TBPMovementSpeedModifierBuff.generated.h"

UCLASS()
class TESTBUFFPROJECT_API UTBPMovementSpeedModifierBuff : public UTBPLastingBuff
{
	GENERATED_BODY()
public:
	UTBPMovementSpeedModifierBuff();
	
	virtual void Activate(ATBPBaseCharacter* Target) const override;
	virtual void OnEndBuff(ATBPBaseCharacter* Target) const override;
	
	virtual void SetParameters(const FTBPBuffSettings& BuffSettings) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float SpeedModifier = 0.2f;
};
