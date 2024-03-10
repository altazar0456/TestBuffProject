// Test Buff Project. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TBPProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class ATBPProjectile : public AActor
{
	GENERATED_BODY()
public:
	ATBPProjectile();
	void SetShotDirection(const FVector& Direction);
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	virtual void BeginPlay() override;
private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, FVector Vector, const FHitResult& HitResult);
};
