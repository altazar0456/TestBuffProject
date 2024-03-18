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
	EndBuff(Buff, true);

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
	FTimerDelegate EndDelegate = FTimerDelegate::CreateUObject(this, &UTBPBuffSystemComponent::EndBuff, Buff, false);	
	World->GetTimerManager().SetTimer(BuffData.EndHandle, EndDelegate, BuffDuration, false);
	
	AppliedBuffs.Add(Buff->GetGameplayTag(), BuffData);

	OnBuffChanged.Broadcast(GetBuffStatusText());
}

void UTBPBuffSystemComponent::TickBuff(UTBPBaseBuff* Buff, float DeltaTime)
{	
	Buff->TickBuff(CharacterOwner, DeltaTime);
}

void UTBPBuffSystemComponent::EndBuff(UTBPBaseBuff* Buff, bool bIsInterrupted)
{
	UWorld* World = GetWorld();
	if(!World || !Buff)
	{
		return;
	}
	
	const FGameplayTag& BuffTag = Buff->GetGameplayTag();
	FBuffData* BuffData = AppliedBuffs.Find(BuffTag);
	if (BuffData)
	{
        World->GetTimerManager().ClearTimer(BuffData->TickHandle);
        World->GetTimerManager().ClearTimer(BuffData->EndHandle);

		if (BuffData->Buff)
		{
			BuffData->Buff->OnEndBuff(CharacterOwner, bIsInterrupted);
		}
		
		AppliedBuffs.Remove(BuffTag);
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

		if(!BuffData.Buff)
		{
			continue;
		}
		const FGameplayTag& Tag = BuffData.Buff->GetGameplayTag();
		BuffStatus += Tag.GetTagName().ToString() + "|";
	}
	
	return FText::FromString(BuffStatus);
}