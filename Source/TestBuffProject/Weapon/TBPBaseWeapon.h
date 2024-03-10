// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TBPBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class ATBPBaseWeapon : public AActor
{
	GENERATED_BODY()
public:
	ATBPBaseWeapon();
	
	virtual void StartFire();
	virtual void StopFire();
	bool IsFiring() const;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	bool bFireInProgress = false;
	
	virtual void BeginPlay() override;
	
	virtual void MakeShot();
};
