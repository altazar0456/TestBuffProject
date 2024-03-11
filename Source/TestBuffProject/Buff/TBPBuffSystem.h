// Test Buff Project. All Rights Reserved.

#pragma once

class UWorld;
class UTBPBaseBuff;

namespace TBPBuffSystem
{
	void ApplyBuffInRadius(UWorld* World, UTBPBaseBuff* Buff, const FVector& Location, float Radius);
}
