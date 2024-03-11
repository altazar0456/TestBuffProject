// Test Buff Project. All Rights Reserved.

#include "TBPBuffSystemComponent.h"

#include "TBPBaseBuff.h"
#include "Player/TBPBaseCharacter.h"

UTBPBuffSystemComponent::UTBPBuffSystemComponent()
{
	
}

void UTBPBuffSystemComponent::ApplyBuff(UTBPBaseBuff* Buff)
{
	//TODO: Keep Owner in class properties 
	ATBPBaseCharacter* Character = Cast<ATBPBaseCharacter>(GetOwner());

	Buff->Apply(Character);
}
