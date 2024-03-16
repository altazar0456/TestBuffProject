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

	CurrentWeaponIndex = 0;
	SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UTBPWeaponComponent::SpawnWeapons()
{
	static const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);		
	static const FName WeaponSocketName = FName(TEXT("WeaponSocket"));
	
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
	
	for (TSubclassOf<ATBPBaseWeapon> WeaponClass : WeaponClasses)
	{
		ATBPBaseWeapon* Weapon = GetWorld()->SpawnActor<ATBPBaseWeapon>(WeaponClass);
		if (!Weapon) continue;

		Weapon->SetOwner(Character);
		Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponSocketName);
		Weapon->SetActorHiddenInGame(true);
		Weapon->SetOwner(GetOwner());
		
		Weapons.Add(Weapon);
	}
}

void UTBPWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid weapon index"));
		return;
	}
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		CurrentWeapon->SetActorHiddenInGame(true);
	}
	
	
	CurrentWeapon = Weapons[WeaponIndex];
	CurrentWeapon->SetActorHiddenInGame(false);
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