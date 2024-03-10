// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TBPBaseWeapon.h"
#include "TBPLauncherWeapon.generated.h"

UCLASS()
class ATBPLauncherWeapon : public ATBPBaseWeapon
{
	GENERATED_BODY()
	
public:	
	virtual void StartFire() override;
	
protected:
	virtual void MakeShot() override;
};
