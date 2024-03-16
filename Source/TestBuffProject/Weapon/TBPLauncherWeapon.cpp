// Test Buff Project. All Rights Reserved.

#include "TBPLauncherWeapon.h"

void ATBPLauncherWeapon::StartFire()
{	
	Super::StartFire();
	
	MakeShot();
	
	StopFire();
}