// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TBPBuffSystem.h"
#include "Components/ActorComponent.h"
#include "TBPBuffSystemComponent.generated.h"

class UTBPBaseBuff;
class ATBPBaseCharacter;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffChangedSignature, FText);

USTRUCT()
struct FBuffData
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(Transient)
	UTBPBaseBuff* Buff = nullptr;
	
    FTimerHandle TickHandle;
    FTimerHandle EndHandle;
};

UCLASS()
class TESTBUFFPROJECT_API UTBPBuffSystemComponent : public UActorComponent
{
    GENERATED_BODY()
	
public:
	
	FOnBuffChangedSignature OnBuffChanged;
	
	virtual void OnRegister() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    FText GetBuffStatusText();
	void ApplyBuff(UTBPBaseBuff* Buff);

protected:
	
	UPROPERTY(Transient)
	ATBPBaseCharacter* CharacterOwner;
	
	UPROPERTY(Transient)
	TMap<FGameplayTag, FBuffData> AppliedBuffs;

	void TickBuff(UTBPBaseBuff* Buff, float DeltaTime);
	void EndBuff(UTBPBaseBuff* Buff, bool bIsInterrupted);
};
