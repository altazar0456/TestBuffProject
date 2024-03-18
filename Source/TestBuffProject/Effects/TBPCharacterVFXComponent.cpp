// Test Buff Project. All Rights Reserved.

#include "TBPCharacterVFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Player/TBPBaseCharacter.h"


void UTBPCharacterVFXComponent::OnRegister()
{
	Super::OnRegister();

	ATBPBaseCharacter* Character = Cast<ATBPBaseCharacter>(GetOwner());
	check(Character);
	CharacterMesh = Character->GetMesh();
	check(CharacterMesh);
}

void UTBPCharacterVFXComponent::ApplyEffect(UNiagaraSystem* Effect)
{
	if(CurrentEffects.Contains(Effect))
	{
		return;
	}
	
	UNiagaraComponent* CurrNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(Effect, CharacterMesh, FName(), FVector::ZeroVector, FRotator::ZeroRotator,
		EAttachLocation::Type::KeepRelativeOffset, false);
	CurrNiagaraComponent->CastShadow = true;

	CurrentEffects.Add(Effect, CurrNiagaraComponent);
}

void UTBPCharacterVFXComponent::FinishEffect(UNiagaraSystem* Effect)
{
	UNiagaraComponent** CurrNiagaraComponentPtr = CurrentEffects.Find(Effect);

	if(CurrNiagaraComponentPtr)
	{
		if(UNiagaraComponent* CurrNiagaraComponent = *CurrNiagaraComponentPtr)
		{
			CurrNiagaraComponent->DestroyInstance();
		}

		CurrentEffects.Remove(Effect);
	}
}