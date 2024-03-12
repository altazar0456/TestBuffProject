// Test Buff Project. All Rights Reserved.

#include "TBPMovementSpeedModifierBuff.h"
#include "Movement/TBPCharacterMovementComponent.h"
#include "Player/TBPBaseCharacter.h"

void UTBPMovementSpeedModifierBuff::Activate(ATBPBaseCharacter* Target) const
{
	//TODO: rewrite it
	UTBPCharacterMovementComponent* MovementComponent = Cast<UTBPCharacterMovementComponent>(Target->GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->SetSpeedModifier(SpeedModifier);
	}	
}

void UTBPMovementSpeedModifierBuff::OnEndBuff(ATBPBaseCharacter* Target) const
{
	//TODO: rewrite it
	UTBPCharacterMovementComponent* MovementComponent = Cast<UTBPCharacterMovementComponent>(Target->GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->SetSpeedModifier(1.0f);
	}
	
}