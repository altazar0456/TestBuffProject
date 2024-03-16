// Test Buff Project. All Rights Reserved.

#include "TBPBuffSystemComponent.h"

#include "TBPBaseBuff.h"
#include "Player/TBPBaseCharacter.h"


void UTBPBuffSystemComponent::OnRegister()
{
	Super::OnRegister();

	CharacterOwner = Cast<ATBPBaseCharacter>(GetOwner());
	check(CharacterOwner);
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
				BuffData.Buff->OnEndBuff(CharacterOwner, true);
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
	
	// Can be only one Buff at the same type
	EndBuff(Buff->BuffType, true);

	Buff->Activate(CharacterOwner);

	if(Buff->IsInstant())
	{
		Buff->OnEndBuff(CharacterOwner, false);
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
	FTimerDelegate EndDelegate = FTimerDelegate::CreateUObject(this, &UTBPBuffSystemComponent::EndBuff, Buff->BuffType, false);	
	World->GetTimerManager().SetTimer(BuffData.EndHandle, EndDelegate, BuffDuration, false);
	
	AppliedBuffs.Add(Buff->BuffType, BuffData);

	OnBuffChanged.Broadcast(GetBuffStatusText());
}

void UTBPBuffSystemComponent::TickBuff(UTBPBaseBuff* Buff, float DeltaTime)
{	
	Buff->TickBuff(CharacterOwner, DeltaTime);
}

void UTBPBuffSystemComponent::EndBuff(ETBPBuffType BuffType, bool bIsInterrupted)
{
	UWorld* World = GetWorld();
	if(!World)
	{
		return;
	}
	
	FBuffData* BuffData = AppliedBuffs.Find(BuffType);
	if (BuffData)
	{
        World->GetTimerManager().ClearTimer(BuffData->TickHandle);
        World->GetTimerManager().ClearTimer(BuffData->EndHandle);

		if (BuffData->Buff)
		{
			BuffData->Buff->OnEndBuff(CharacterOwner, bIsInterrupted);
		}
		
		AppliedBuffs.Remove(BuffType);
		OnBuffChanged.Broadcast(GetBuffStatusText());
	}	
}

//TODO: Maybe return const FText&, but then we will need to keep this text somewhere. But looks like FText will not copy all text
FText UTBPBuffSystemComponent::GetBuffStatusText()
{
	if (AppliedBuffs.Num() == 0)
	{
		return FText::GetEmpty();
	}
	
	//TODO: Maybe construct FText instead of FString.
	FString BuffStatus = "|";
	for (auto BuffDataPair : AppliedBuffs)
	{
		const FBuffData& BuffData = BuffDataPair.Value;

		BuffStatus += BuffData.Buff->GetName() + "|";
	}
	
	return FText::FromString(BuffStatus);
}