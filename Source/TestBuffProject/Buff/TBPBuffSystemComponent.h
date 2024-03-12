// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TBPBuffSystemComponent.generated.h"

class UTBPBaseBuff;
class ATBPBaseCharacter;

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
	UTBPBuffSystemComponent();
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	void ApplyBuff(UTBPBaseBuff* Buff);

protected:
	
	UPROPERTY(Transient)
	ATBPBaseCharacter* CharacterOwner;
	
	//TODO: maybe use Map with key as FName or Tag
	UPROPERTY(Transient)
	TMap<TSubclassOf<UTBPBaseBuff>, FBuffData> AppliedBuffs;

	void TickBuff(UTBPBaseBuff* Buff, float DeltaTime);
	void EndBuff(UClass* BuffClass);
};
