// Test Buff Project. All Rights Reserved.

#include "TBPBaseBuff.h"

#include "Effects/TBPCharacterVFXComponent.h"
#include "Player/TBPBaseCharacter.h"

void UTBPLastingBuff::Activate(ATBPBaseCharacter* Target)
{
	Super::Activate(Target);
	
	if (BuffVFX)
	{
		Target->VFXComponent->ApplyEffect(BuffVFX);
	}
}

void UTBPLastingBuff::OnEndBuff(ATBPBaseCharacter* Target, bool bIsInterrupted)
{	
	if (BuffVFX)
	{
		Target->VFXComponent->FinishEffect(BuffVFX);
	}
	
	Super::OnEndBuff(Target, bIsInterrupted);
}

void UTBPLastingBuff::SetParameters(const FTBPBuffSettings& BuffSettings)
{
	Super::SetParameters(BuffSettings);
	
	Duration = BuffSettings.Duration;
	TickDeltaTime = BuffSettings.TickDeltaTime;
	BuffVFX = BuffSettings.BuffVFX;
}
