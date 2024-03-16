// Test Buff Project. All Rights Reserved.

#include "TBPDamageOverTimeBuff.h"
#include "Health/TBPHealthComponent.h"
#include "Player/TBPBaseCharacter.h"

UTBPDamageOverTimeBuff::UTBPDamageOverTimeBuff()
{
	BuffType = ETBPBuffType::DamageOverTime;
	bInstanced = true;
}

void UTBPDamageOverTimeBuff::SetParameters(const FTBPBuffSettings& BuffSettings)
{
	Super::SetParameters(BuffSettings);	
	
	Damage = BuffSettings.Value;
}

void UTBPDamageOverTimeBuff::Activate(ATBPBaseCharacter* Target)
{
	Super::Activate(Target);

	AppliedDamage = 0.0f;
}

void UTBPDamageOverTimeBuff::TickBuff(ATBPBaseCharacter* Target, float DeltaTime)
{
	Super::TickBuff(Target, DeltaTime);

	const float CurrentPercentTime = DeltaTime / Duration;
	const float CurrentDamage = CurrentPercentTime * Damage;
	//TODO: rewrite it
	Target->HealthComponent->ApplyDamage(CurrentDamage);
	AppliedDamage += CurrentDamage;
}

void UTBPDamageOverTimeBuff::OnEndBuff(ATBPBaseCharacter* Target, bool bIsInterrupted)
{
	if(!bIsInterrupted)
	{
		const float DeltaDamage = Damage - AppliedDamage;

		if(DeltaDamage < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Character received more damage than expected"));
		}
		else
		{
			Target->HealthComponent->ApplyDamage(DeltaDamage);
		}
	}
	
	Super::OnEndBuff(Target, bIsInterrupted);
}
