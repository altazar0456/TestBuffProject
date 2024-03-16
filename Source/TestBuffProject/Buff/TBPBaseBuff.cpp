// Test Buff Project. All Rights Reserved.

#include "TBPBaseBuff.h"

void UTBPLastingBuff::SetParameters(const FTBPBuffSettings& BuffSettings)
{
	Super::SetParameters(BuffSettings);
	
	Duration = BuffSettings.Duration;
	TickDeltaTime = BuffSettings.TickDeltaTime;
}
