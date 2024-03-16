﻿// Test Buff Project. All Rights Reserved.

#include "TBPMovementSpeedModifierBuff.h"
#include "Movement/TBPCharacterMovementComponent.h"
#include "Player/TBPBaseCharacter.h"

UTBPMovementSpeedModifierBuff::UTBPMovementSpeedModifierBuff()
{
	BuffType = ETBPBuffType::MovementSpeedModifier;
}

void UTBPMovementSpeedModifierBuff::SetParameters(const FTBPBuffSettings& BuffSettings)
{
	Super::SetParameters(BuffSettings);	
	
	SpeedModifier = BuffSettings.Value;
}

void UTBPMovementSpeedModifierBuff::Activate(ATBPBaseCharacter* Target)
{
	//TODO: rewrite it
	UTBPCharacterMovementComponent* MovementComponent = Cast<UTBPCharacterMovementComponent>(Target->GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->SetSpeedModifier(SpeedModifier);
	}	
}

void UTBPMovementSpeedModifierBuff::OnEndBuff(ATBPBaseCharacter* Target, bool bIsInterrupted)
{
	//TODO: rewrite it
	UTBPCharacterMovementComponent* MovementComponent = Cast<UTBPCharacterMovementComponent>(Target->GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->SetSpeedModifier(1.0f);
	}
	
}