// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TBPWeaponComponent.generated.h"

class ATBPBaseWeapon;

UCLASS()
class UTBPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ATBPBaseWeapon> WeaponClass;
	
public:	
	UTBPWeaponComponent();

	void StartFire();
	void StopFire();

protected:
	virtual void BeginPlay() override;

	void SpawnWeapon();

private:
	UPROPERTY()
	ATBPBaseWeapon* CurrentWeapon = nullptr;	
};
