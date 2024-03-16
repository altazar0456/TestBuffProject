// Test Buff Project. All Rights Reserved.

#include "TBPDamageBuff.h"

#include "Health/TBPHealthComponent.h"
#include "Player/TBPBaseCharacter.h"

UTBPDamageBuff::UTBPDamageBuff()
{
	BuffType = ETBPBuffType::InstantDamage;
}

void UTBPDamageBuff::Activate(ATBPBaseCharacter* Target) const
{
	Super::Activate(Target);
	
	//TODO: rewrite it
	Target->HealthComponent->ApplyDamage(Damage);
}
