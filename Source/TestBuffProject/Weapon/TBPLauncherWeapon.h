﻿// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TBPBaseWeapon.h"
#include "Buff/TBPBuffSystem.h"
#include "TBPLauncherWeapon.generated.h"

class ATBPProjectile;

UCLASS()
class TESTBUFFPROJECT_API ATBPLauncherWeapon : public ATBPBaseWeapon
{
	GENERATED_BODY()
	
public:	
	virtual void StartFire() override;
};
