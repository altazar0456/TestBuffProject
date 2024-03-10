// Test Buff Project. All Rights Reserved.

#include "TBPLauncherWeapon.h"

void ATBPLauncherWeapon::StartFire()
{	
	Super::StartFire();
	
	MakeShot();
}

void ATBPLauncherWeapon::MakeShot()
{
	UE_LOG(LogTemp, Log, TEXT("Shot projectile from Launcher weapon"));
	
	StopFire();
}