// Test Buff Project. All Rights Reserved.

#include "TBPLauncherWeapon.h"
#include "TBPProjectile.h"
#include "DrawDebugHelpers.h"

void ATBPLauncherWeapon::StartFire()
{	
	Super::StartFire();
	
	MakeShot();
}

void ATBPLauncherWeapon::MakeShot()
{
	UE_LOG(LogTemp, Log, TEXT("Shot projectile from Launcher weapon"));
	
	FVector TraceStart;
	FVector TraceEnd;
	if(GetProjectileTraceData(TraceStart, TraceEnd))
	{		
		const FVector MuzzleLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);
		const FTransform SpawnTransform(FRotator::ZeroRotator, MuzzleLocation);
		const FVector Direction = (TraceEnd - MuzzleLocation).GetSafeNormal();

		ATBPProjectile* Projectile = GetWorld()->SpawnActorDeferred<ATBPProjectile>(ProjectileClass, SpawnTransform);
		if(Projectile)
		{
			Projectile->SetShotDirection(Direction);
			Projectile->SetOwner(GetOwner());
			Projectile->FinishSpawning(SpawnTransform);
		}
		
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Orange, false, 3.0f, 0, 3.0f);
	}
	
	StopFire();
}