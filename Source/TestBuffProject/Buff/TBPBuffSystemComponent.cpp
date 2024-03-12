// Test Buff Project. All Rights Reserved.

#include "TBPBuffSystemComponent.h"

#include "TBPBaseBuff.h"
#include "Player/TBPBaseCharacter.h"

UTBPBuffSystemComponent::UTBPBuffSystemComponent()
{
	
}

void UTBPBuffSystemComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if (UWorld* World = GetWorld())
	{
		for (auto BuffDataPair : AppliedBuffs)
		{
			FBuffData BuffData = BuffDataPair.Value;
			World->GetTimerManager().ClearTimer(BuffData.TickHandle);
			World->GetTimerManager().ClearTimer(BuffData.EndHandle);

			if (BuffData.Buff)
			{
				//TODO: Keep Owner in class properties 
				ATBPBaseCharacter* Character = Cast<ATBPBaseCharacter>(GetOwner());
				BuffData.Buff->OnEndBuff(Character);
			}
		}
	}
	
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UTBPBuffSystemComponent::ApplyBuff(UTBPBaseBuff* Buff)
{
	UWorld* World = GetWorld();
	if(!World)
	{
		return;
	}
	//TODO: Implement instanced behaviour where each Buff can have their own runtime memory
	
	// Can be only one Buff at the same type
	EndBuff(Buff->GetClass());
	
	//TODO: Keep Owner in class properties 
	ATBPBaseCharacter* Character = Cast<ATBPBaseCharacter>(GetOwner());

	Buff->Activate(Character);

	if(Buff->IsInstant())
	{
		Buff->OnEndBuff(Character);
		return;
	}

	const float BuffDuration = Buff->GetDuration();
	const float BuffDeltaTime = Buff->GetTickPeriod();
	check(BuffDuration > 0);
	check(BuffDeltaTime > 0);
	FBuffData BuffData;
	BuffData.Buff = Buff;
	
	FTimerDelegate TickDelegate = FTimerDelegate::CreateUObject( this, &UTBPBuffSystemComponent::TickBuff, Buff, BuffDeltaTime);	
	World->GetTimerManager().SetTimer(BuffData.TickHandle, TickDelegate, BuffDeltaTime, true);
	FTimerDelegate EndDelegate = FTimerDelegate::CreateUObject(this, &UTBPBuffSystemComponent::EndBuff, Buff->GetClass());	
	World->GetTimerManager().SetTimer(BuffData.EndHandle, EndDelegate, BuffDuration, false);
	
	AppliedBuffs.Add(Buff->GetClass(), BuffData);
}

void UTBPBuffSystemComponent::TickBuff(UTBPBaseBuff* Buff, float DeltaTime)
{
	//TODO: Keep Owner in class properties 
	ATBPBaseCharacter* Character = Cast<ATBPBaseCharacter>(GetOwner());
	
	Buff->TickBuff(Character, DeltaTime);
}

void UTBPBuffSystemComponent::EndBuff(UClass* BuffClass)
{
	UWorld* World = GetWorld();
	if(!World)
	{
		return;
	}
	
	FBuffData* BuffData = AppliedBuffs.Find(BuffClass);
	if (BuffData)
	{
        World->GetTimerManager().ClearTimer(BuffData->TickHandle);
        World->GetTimerManager().ClearTimer(BuffData->EndHandle);

		if (BuffData->Buff)
		{
			//TODO: Keep Owner in class properties 
			ATBPBaseCharacter* Character = Cast<ATBPBaseCharacter>(GetOwner());
			BuffData->Buff->OnEndBuff(Character);
		}
		
		AppliedBuffs.Remove(BuffClass);
	}	
}