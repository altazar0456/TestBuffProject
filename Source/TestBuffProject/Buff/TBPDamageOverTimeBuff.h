// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TBPBaseBuff.h"
#include "TBPDamageOverTimeBuff.generated.h"

UCLASS()
class TESTBUFFPROJECT_API UTBPDamageOverTimeBuff : public UTBPLastingBuff
{
	GENERATED_BODY()
public:
	UTBPDamageOverTimeBuff();
	//TODO: Make this class instanced, count damage and OnEnd apply all remaining damage
	virtual void TickBuff(ATBPBaseCharacter* Target, float DeltaTime) const override;

	//TODO: make property protected. change the way of initialization
//protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float Damage = 20.0f;
};
