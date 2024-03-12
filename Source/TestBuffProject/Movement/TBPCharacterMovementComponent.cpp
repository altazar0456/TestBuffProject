// Test Buff Project. All Rights Reserved.

#include "TBPCharacterMovementComponent.h"

float UTBPCharacterMovementComponent::GetMaxSpeed() const
{
	const float BaseSpeed = Super::GetMaxSpeed(); 
	return SpeedModifier * BaseSpeed;
}
void UTBPCharacterMovementComponent::SetSpeedModifier(float NewSpeed)
{
	SpeedModifier = NewSpeed;
}
