// Test Buff Project. All Rights Reserved.

#include "TBPBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

ATBPBaseWeapon::ATBPBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ATBPBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

void ATBPBaseWeapon::StartFire()
{
	bFireInProgress = true;
}

void ATBPBaseWeapon::StopFire()
{
	bFireInProgress = false;
}

bool ATBPBaseWeapon::IsFiring() const
{
	return bFireInProgress;
}

void ATBPBaseWeapon::MakeShot() {}