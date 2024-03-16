// Test Buff Project. All Rights Reserved.

#include "TBPBuffSystem.h"

#include "TBPBaseBuff.h"
#include "Weapon/TBPProjectile.h"
#include "TBPBuffSystemComponent.h"
#include "TBPDamageBuff.h"
#include "TBPDamageOverTimeBuff.h"
#include "TBPMovementSpeedModifierBuff.h"
#include "Weapon/TBPBaseWeapon.h"

void TBPBuffSystem::ApplyBuffInRadius(UWorld* World, const UTBPBaseBuff* Buff, const FVector& Location, float Radius)
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

ATBPProjectile* TBPBuffSystem::SpawnProjectile(UWorld* World, ATBPBaseWeapon* Weapon, const UDataTable* BuffDataTable, ETBPBuffType ProjectileBuffType,
	const FVector& Location, const FVector& Direction)
{
	//TODO: Add DataTable to condition
	//TODO: Get data from DataTable
	if (!World || !Weapon || !BuffDataTable)
	{
		return nullptr;
	}
	
	const FTransform SpawnTransform(FRotator::ZeroRotator, Location);

	ATBPProjectile* Projectile = World->SpawnActorDeferred<ATBPProjectile>(ATBPProjectile::StaticClass(), SpawnTransform);
	if(Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(Weapon);
		
		SetProjectileParameters(Projectile, BuffDataTable, ProjectileBuffType);
		
		Projectile->FinishSpawning(SpawnTransform);
	}

	return Projectile;
}

void TBPBuffSystem::SetProjectileParameters(ATBPProjectile* Projectile, const UDataTable* BuffDataTable, ETBPBuffType ProjectileBuffType)
{
	//TODO: cache values? Replace TEXT to something from reflection
	//TODO: make Maps with this key inside GameMode or some inherited class
	TArray<FTBPBuffSettings*> BuffSettingsArray;
	BuffDataTable->GetAllRows<FTBPBuffSettings>(TEXT("BuffSettings"), BuffSettingsArray);

	FTBPBuffSettings* BuffSettings = nullptr;
	for (FTBPBuffSettings* CurrBuffSettings : BuffSettingsArray)
	{
		if(CurrBuffSettings->BuffType == ProjectileBuffType)
		{
			BuffSettings = CurrBuffSettings;
		}
	}

	if(!BuffSettings)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't create buf for this Projectile. Check DataTable for Buffs"));
		Projectile->Buff = nullptr;
		return;
	}

	//TODO: Make factory class where this function will be implemented for each type
	switch (ProjectileBuffType)
	{
	case ETBPBuffType::InstantDamage:
	{
		UTBPDamageBuff* DamageBuff = NewObject<UTBPDamageBuff>();
		DamageBuff->Damage = BuffSettings->Value;
		Projectile->Buff = DamageBuff;
		break;
	}		
	case ETBPBuffType::DamageOverTime:
	{
		UTBPDamageOverTimeBuff* DamageOverTimeBuff = NewObject<UTBPDamageOverTimeBuff>();
		DamageOverTimeBuff->Duration = BuffSettings->Duration;
		DamageOverTimeBuff->TickDeltaTime = BuffSettings->TickDeltaTime;
		DamageOverTimeBuff->Damage = BuffSettings->Value;
		Projectile->Buff = DamageOverTimeBuff;
		break;
	}		
	case ETBPBuffType::MovementSpeedModifier:
	{
		UTBPMovementSpeedModifierBuff* MovementSpeedModifierBuff = NewObject<UTBPMovementSpeedModifierBuff>();
		MovementSpeedModifierBuff->Duration = BuffSettings->Duration;
		MovementSpeedModifierBuff->TickDeltaTime = BuffSettings->TickDeltaTime;
		MovementSpeedModifierBuff->SpeedModifier = BuffSettings->Value;
		Projectile->Buff = MovementSpeedModifierBuff;
		break;
	}		
	case ETBPBuffType::Other:
		UE_LOG(LogTemp, Warning, TEXT("Can't create buf for this Projectile."));
		Projectile->Buff = nullptr;
		break;
	}
}