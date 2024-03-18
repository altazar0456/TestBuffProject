// Test Buff Project. All Rights Reserved.

#include "TBPBaseBuff.h"

#include "Effects/TBPCharacterVFXComponent.h"
#include "Player/TBPBaseCharacter.h"

void UTBPLastingBuff::Activate(ATBPBaseCharacter* Target)
{
	Super::Activate(Target);
	
	if (BuffVFX)
	{
		Target->GetVFXComponent()->ApplyEffect(BuffVFX);
	}
}

void UTBPLastingBuff::OnEndBuff(ATBPBaseCharacter* Target, bool bIsInterrupted)
{	
	if (BuffVFX)
	{
		Target->GetVFXComponent()->FinishEffect(BuffVFX);
	}
	
	Super::OnEndBuff(Target, bIsInterrupted);
}

void UTBPLastingBuff::SetParameters(const FTBPBuffSettings& BuffSettings)
{
	Super::SetParameters(BuffSettings);
	
	Duration = BuffSettings.Duration;
	TickDeltaTime = BuffSettings.TickDeltaTime;
	BuffVFX = BuffSettings.BuffVFX;
	BuffTag = BuffSettings.BuffTag;
}
