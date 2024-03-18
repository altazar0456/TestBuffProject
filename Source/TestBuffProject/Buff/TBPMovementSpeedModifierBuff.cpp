// Test Buff Project. All Rights Reserved.

#include "TBPMovementSpeedModifierBuff.h"
#include "Movement/TBPCharacterMovementComponent.h"
#include "Player/TBPBaseCharacter.h"

UTBPMovementSpeedModifierBuff::UTBPMovementSpeedModifierBuff()
{
}

void UTBPMovementSpeedModifierBuff::SetParameters(const FTBPBuffSettings& BuffSettings)
{
	Super::SetParameters(BuffSettings);	
	
	SpeedModifier = BuffSettings.Value;
}

void UTBPMovementSpeedModifierBuff::Activate(ATBPBaseCharacter* Target)
{
	Super::Activate(Target);
	
	UTBPCharacterMovementComponent* MovementComponent = Cast<UTBPCharacterMovementComponent>(Target->GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->SetSpeedModifier(SpeedModifier);
	}	
}

void UTBPMovementSpeedModifierBuff::OnEndBuff(ATBPBaseCharacter* Target, bool bIsInterrupted)
{
	UTBPCharacterMovementComponent* MovementComponent = Cast<UTBPCharacterMovementComponent>(Target->GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->SetSpeedModifier(1.0f);
	}
	
	Super::OnEndBuff(Target, bIsInterrupted);	
}