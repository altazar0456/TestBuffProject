// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TBPCharacterMovementComponent.generated.h"

UCLASS()
class TESTBUFFPROJECT_API UTBPCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()
	
public:
	virtual float GetMaxSpeed() const override;	
	void SetSpeedModifier(float NewSpeed);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float SpeedModifier = 1.0f;	
};
