// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TBPWeaponComponent.generated.h"

class ATBPBaseWeapon;

UCLASS()
class TESTBUFFPROJECT_API UTBPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ATBPBaseWeapon>> WeaponClasses;
	
public:	
	UTBPWeaponComponent();

	void StartFire();
	void StopFire();
	
	void EquipWeapon(int32 WeaponIndex);

protected:
	UPROPERTY(Transient)
	ATBPBaseWeapon* CurrentWeapon = nullptr;
	
	UPROPERTY(Transient)
	TArray<ATBPBaseWeapon*> Weapons;
	
	int32 CurrentWeaponIndex = 0;
	
	virtual void BeginPlay() override;
	void SpawnWeapons();
};
