// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TBPBuffSystem.generated.h"

class UWorld;
class ATBPBaseWeapon;
class ATBPProjectile;
class UTBPBaseBuff;

//TODO: Maybe replace to strings or Gameplay Tags, so it can be extended in blueprint?
UENUM(BlueprintType)
enum class ETBPBuffType : uint8
{
	InstantDamage,
	DamageOverTime,
	MovementSpeedModifier,
	Other
};

USTRUCT(BlueprintType)
struct FTBPBuffSettings : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ETBPBuffType BuffType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsInstant = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Duration = 3.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TickDeltaTime = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Value = 0.0f;
};

namespace TBPBuffSystem
{
	void ApplyBuffInRadius(UWorld* World, const UTBPBaseBuff* Buff, const FVector& Location, float Radius);

	//TODO: Move to some class
	//TODO: Maybe it will be some manager inside GameState or GameMode or GameInstance or somewhere there
	//TODO: so we will have a link for DataTable
	//TODO: Maybe move there whole TBPBuffSystem namespace and make it class
	ATBPProjectile* SpawnProjectile(UWorld* World, ATBPBaseWeapon* Weapon, const UDataTable* BuffDataTable, ETBPBuffType ProjectileBuffType,
		const FVector& Location, const FVector& Direction);

	void SetProjectileParameters(ATBPProjectile* Projectile, const UDataTable* BuffDataTable, ETBPBuffType ProjectileBuffType);
}