// Test Buff Project. All Rights Reserved.

#include "TBPDamageBuff.h"

#include "Health/TBPHealthComponent.h"
#include "Player/TBPBaseCharacter.h"

UTBPDamageBuff::UTBPDamageBuff()
{
	BuffType = ETBPBuffType::InstantDamage;
}

void UTBPDamageBuff::SetParameters(const FTBPBuffSettings& BuffSettings)
{
	Super::SetParameters(BuffSettings);	
	
	Damage = BuffSettings.Value;
}

void UTBPDamageBuff::Activate(ATBPBaseCharacter* Target)
{
	Super::Activate(Target);
	
	//TODO: rewrite it
	Target->HealthComponent->ApplyDamage(Damage);
}