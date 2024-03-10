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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;
	
	bool bFireInProgress = false;
	
	virtual void BeginPlay() override;
	
	virtual void MakeShot();

	//TODO: remove bIsCollided
	bool GetProjectileTraceData(FVector& TraceStart, FVector& TraceEnd) const;
};
