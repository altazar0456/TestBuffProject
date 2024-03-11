// Test Buff Project. All Rights Reserved.

#include "TBPDamageBuff.h"

#include "Health/TBPHealthComponent.h"
#include "Player/TBPBaseCharacter.h"

void UTBPDamageBuff::Apply(ATBPBaseCharacter* Target)
{
	//TODO: rewrite it
	Target->HealthComponent->ApplyDamage(Damage);
}
