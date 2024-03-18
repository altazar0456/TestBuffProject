// Test Buff Project. All Rights Reserved.

#include "TBPDamageOverTimeBuff.h"
#include "Health/TBPHealthComponent.h"
#include "Player/TBPBaseCharacter.h"

UTBPDamageOverTimeBuff::UTBPDamageOverTimeBuff()
{
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

	const float RemainingDamage = Damage - AppliedDamage;
	const float CurrentPercentTime = DeltaTime / Duration;
	float CurrentDamage = CurrentPercentTime * Damage;
	CurrentDamage = FMath::Min(CurrentDamage, RemainingDamage);
	//TODO: rewrite it
	Target->HealthComponent->ApplyDamage(CurrentDamage);
	AppliedDamage += CurrentDamage;
}

void UTBPDamageOverTimeBuff::OnEndBuff(ATBPBaseCharacter* Target, bool bIsInterrupted)
{
	if(!bIsInterrupted)
	{
		const float DeltaDamage = Damage - AppliedDamage;

		if(DeltaDamage < -KINDA_SMALL_NUMBER)
		{
			UE_LOG(LogTemp, Warning, TEXT("Character received more damage (%f) than expected"), -DeltaDamage);
		}
		else
		{
			Target->HealthComponent->ApplyDamage(DeltaDamage);
		}
	}
	
	Super::OnEndBuff(Target, bIsInterrupted);
}
