// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TBPCharacterVFXComponent.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class TESTBUFFPROJECT_API UTBPCharacterVFXComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	virtual void OnRegister() override;

	void ApplyEffect(UNiagaraSystem* Effect);
	void FinishEffect(UNiagaraSystem* Effect);
	
	UPROPERTY(Transient)
	TMap<UNiagaraSystem*, UNiagaraComponent*> CurrentEffects;
	
	UPROPERTY(Transient)
	USkeletalMeshComponent* CharacterMesh;
};
