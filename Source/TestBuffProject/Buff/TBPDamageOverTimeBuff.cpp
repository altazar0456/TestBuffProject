// Test Buff Project. All Rights Reserved.

#include "TBPDamageOverTimeBuff.h"
#include "Health/TBPHealthComponent.h"
#include "Player/TBPBaseCharacter.h"

UTBPDamageOverTimeBuff::UTBPDamageOverTimeBuff()
{
	BuffType = ETBPBuffType::DamageOverTime;
}

void UTBPDamageOverTimeBuff::SetParameters(const FTBPBuffSettings& BuffSettings)
{
	Super::SetParameters(BuffSettings);	
	
	Damage = BuffSettings.Value;
}

void UTBPDamageOverTimeBuff::TickBuff(ATBPBaseCharacter* Target, float DeltaTime) const
{
	Super::TickBuff(Target, DeltaTime);

	const float CurrentPercentTime = DeltaTime / Duration;
	const float CurrentDamage = CurrentPercentTime * Damage;
	//TODO: rewrite it
	Target->HealthComponent->ApplyDamage(CurrentDamage);
}
