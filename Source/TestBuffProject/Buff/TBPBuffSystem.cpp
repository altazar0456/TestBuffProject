// Test Buff Project. All Rights Reserved.

#include "TBPBuffSystem.h"

#include "TBPBaseBuff.h"
#include "Weapon/TBPProjectile.h"
#include "TBPBuffSystemComponent.h"
#include "Weapon/TBPBaseWeapon.h"

void UTBPBuffSystem::OnStartPlay()
{
	check(BuffSettings);
}

void UTBPBuffSystem::ApplyBuffInRadius(UWorld* World, const UTBPBaseBuff* Buff, const FVector& Location, float Radius)
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

ATBPProjectile* UTBPBuffSystem::SpawnProjectile(UWorld* World, ATBPBaseWeapon* Weapon, ETBPBuffType ProjectileBuffType,
	const FVector& Location, const FVector& Direction)
{
	//TODO: Add DataTable to condition
	//TODO: Get data from DataTable
	if (!World || !Weapon)
	{
		return nullptr;
	}
	
	const FTransform SpawnTransform(FRotator::ZeroRotator, Location);

	ATBPProjectile* Projectile = World->SpawnActorDeferred<ATBPProjectile>(ATBPProjectile::StaticClass(), SpawnTransform);
	if(Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(Weapon);
		
		SetProjectileParameters(Projectile, ProjectileBuffType);
		
		Projectile->FinishSpawning(SpawnTransform);
	}

	return Projectile;
}

void UTBPBuffSystem::SetProjectileParameters(ATBPProjectile* Projectile, ETBPBuffType ProjectileBuffType)
{
	//TODO: cache values? Replace TEXT to something from reflection
	//TODO: make Maps with this key inside GameMode or some inherited class
	TArray<FTBPBuffSettings*> BuffSettingsRows;
	BuffSettings->GetAllRows<FTBPBuffSettings>(TEXT("BuffSettings"), BuffSettingsRows);

	FTBPBuffSettings* BuffSettingsRow = nullptr;
	for (FTBPBuffSettings* CurrBuffSettingsRow : BuffSettingsRows)
	{
		if(CurrBuffSettingsRow->BuffType == ProjectileBuffType)
		{
			BuffSettingsRow = CurrBuffSettingsRow;
		}
	}

	if(!BuffSettingsRow || ProjectileBuffType == ETBPBuffType::Other || BuffSettingsRow->BuffClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't create buf for this Projectile. Check DataTable for Buffs"));
		Projectile->Buff = nullptr;
		return;
	}
	
	Projectile->Buff = NewObject<UTBPBaseBuff>(GetTransientPackage(), BuffSettingsRow->BuffClass);
	Projectile->Buff->SetParameters(*BuffSettingsRow);
}