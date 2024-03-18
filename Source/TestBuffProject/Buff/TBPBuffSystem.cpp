// Test Buff Project. All Rights Reserved.

#include "TBPBuffSystem.h"

#include "DrawDebugHelpers.h"
#include "TBPBaseBuff.h"
#include "Weapon/TBPProjectile.h"
#include "TBPBuffSystemComponent.h"
#include "Weapon/TBPBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogTBPBuffSystem, All, All);

void UTBPBuffSystem::OnStartPlay()
{
	check(BuffSettings);
	
	TArray<FTBPBuffSettings*> BuffSettingsRows;
	BuffSettings->GetAllRows<FTBPBuffSettings>(TEXT("BuffSettings"), BuffSettingsRows);
	
	for (const FTBPBuffSettings* CurrBuffSettingsRow : BuffSettingsRows)
	{
		BuffSettingsMap.Add(CurrBuffSettingsRow->BuffTag, *CurrBuffSettingsRow);
	}
}

void UTBPBuffSystem::ApplyBuffInRadius(UWorld* World, UTBPBaseBuff* Buff, const FVector& Location, float Radius) const
{
	if (!World || Radius <= 0)
	{
		return;
	}
	
	TArray<FOverlapResult> OutOverlaps;
	FCollisionShape SphereShape;
	SphereShape.SetSphere(Radius);

	const bool bHit = World->OverlapMultiByChannel(OutOverlaps, Location, FQuat::Identity, ECollisionChannel::ECC_Visibility, SphereShape);

	if (bHit)
	{		
		for (FOverlapResult OverlapResult : OutOverlaps)
		{
			const AActor* Actor = OverlapResult.GetActor();
			UTBPBuffSystemComponent* BuffSystemComponent = Actor ? Cast<UTBPBuffSystemComponent>(Actor->GetComponentByClass(UTBPBuffSystemComponent::StaticClass())) : nullptr;

			UTBPBaseBuff* CurrentBuff = Buff;
			if(Buff->IsInstanced())
			{
				CurrentBuff = DuplicateObject(Buff, GetTransientPackage());
			}
			
			if(BuffSystemComponent)
			{
				BuffSystemComponent->ApplyBuff(CurrentBuff);				
			}
		}
	}
}

ATBPProjectile* UTBPBuffSystem::SpawnProjectile(UWorld* World, ATBPBaseWeapon* Weapon, const FGameplayTag& BuffTag,
	const FVector& Location, const FVector& Direction) const
{
	if (!World || !Weapon || !Weapon->ProjectileClass)
	{
		UE_LOG(LogTBPBuffSystem, Log, TEXT("No World or Weapon to spawn projectile"));
		return nullptr;
	}
	
	const FTransform SpawnTransform(FRotator::ZeroRotator, Location);

	ATBPProjectile* Projectile = World->SpawnActorDeferred<ATBPProjectile>(Weapon->ProjectileClass, SpawnTransform);
	if(Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(Weapon);
		
		SetProjectileParameters(Projectile, BuffTag);
		
		Projectile->FinishSpawning(SpawnTransform);
	}

	return Projectile;
}

void UTBPBuffSystem::SetProjectileParameters(ATBPProjectile* Projectile, const FGameplayTag& BuffTag) const
{
	const FTBPBuffSettings* BuffSettingsRow = BuffSettingsMap.Find(BuffTag);

	if(!BuffSettingsRow || BuffSettingsRow->BuffClass == nullptr)
	{
		UE_LOG(LogTBPBuffSystem, Warning, TEXT("Can't create buf for this Projectile. Check DataTable for Buffs"));
		Projectile->Buff = nullptr;
		return;
	}
	
	Projectile->Buff = NewObject<UTBPBaseBuff>(GetTransientPackage(), BuffSettingsRow->BuffClass);
	Projectile->Buff->SetParameters(*BuffSettingsRow);
}