// Test Buff Project. All Rights Reserved.

#include "TBPBuffSystem.h"
#include "TBPBaseBuff.h"
#include "TBPBuffSystemComponent.h"
#include "TBPDamageBuff.h"

void TBPBuffSystem::ApplyBuffInRadius(UWorld* World, UTBPBaseBuff* Buff, const FVector& Location, float Radius)
{
	if (!World || Radius <= 0)
	{
		return;
	}
	
	TArray<FOverlapResult> OutOverlaps;
	FCollisionShape SphereShape;
	SphereShape.SetSphere(Radius);

	//TODO: replace to async function. will need to use UObject class for this instead. Maybe it will be "SingleTone" part of GameInstance
	const bool bHit = World->OverlapMultiByChannel(OutOverlaps, Location, FQuat::Identity, ECollisionChannel::ECC_Visibility, SphereShape);

	if (bHit)
	{		
		for (FOverlapResult OverlapResult : OutOverlaps)
		{
			const AActor* Actor = OverlapResult.GetActor();
			UTBPBuffSystemComponent* BuffSystemComponent = Actor ? Cast<UTBPBuffSystemComponent>(Actor->GetComponentByClass(UTBPBuffSystemComponent::StaticClass())) : nullptr;

			if(BuffSystemComponent)
			{
				//TODO: check that it's okay to paste one buff everywhere
				BuffSystemComponent->ApplyBuff(Buff);				
			}
		}
	}
}
