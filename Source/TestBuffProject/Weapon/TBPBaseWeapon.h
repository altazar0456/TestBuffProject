// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TBPProjectile.h"
#include "Buff/TBPBuffSystem.h"
#include "TBPBaseWeapon.generated.h"

class ATBPProjectile;
class USkeletalMeshComponent;

UCLASS()
class TESTBUFFPROJECT_API ATBPBaseWeapon : public AActor
{
	GENERATED_BODY()
public:
	ATBPBaseWeapon();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ATBPProjectile> ProjectileClass;
	
	virtual void StartFire();
	virtual void StopFire();
	bool IsFiring() const;
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FGameplayTag BuffTag;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;
	
	bool bFireInProgress = false;
	
	virtual void BeginPlay() override;
	
	virtual void MakeShot();

	bool GetProjectileTraceData(FVector& TraceStart, FVector& TraceEnd) const;
};
