// Test Buff Project. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TBPProjectile.generated.h"

class UTBPBaseBuff;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TESTBUFFPROJECT_API ATBPProjectile : public AActor
{
	GENERATED_BODY()
public:
	ATBPProjectile();
	void SetShotDirection(const FVector& Direction);

	//TODO: Move to Protected
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UTBPBaseBuff* Buff = nullptr;
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Radius = 200.0f;

	virtual void BeginPlay() override;
private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, FVector Vector, const FHitResult& HitResult);
};
