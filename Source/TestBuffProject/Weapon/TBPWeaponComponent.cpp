// Test Buff Project. All Rights Reserved.

#include "TBPWeaponComponent.h"
#include "TBPBaseWeapon.h"
#include "GameFramework/Character.h"

UTBPWeaponComponent::UTBPWeaponComponent()
{
}

void UTBPWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();	
}

void UTBPWeaponComponent::SpawnWeapon()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character)
	{
		return;
	}

	CurrentWeapon = World->SpawnActor<ATBPBaseWeapon>(WeaponClass);
	if(!CurrentWeapon)
	{
		return;
	}
	
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);		
	const FName WeaponSocketName = FName(TEXT("WeaponSocket"));
	
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponSocketName);
}

void UTBPWeaponComponent::StartFire()
{
	if(!CurrentWeapon)
	{
		return;
	}

	CurrentWeapon->StartFire();
}

void UTBPWeaponComponent::StopFire()
{
	if(!CurrentWeapon)
	{
		return;
	}

	CurrentWeapon->StopFire();
}