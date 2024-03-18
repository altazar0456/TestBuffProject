// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "TBPBuffSystem.generated.h"

class UWorld;
class ATBPBaseWeapon;
class ATBPProjectile;
class UTBPBaseBuff;
class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FTBPBuffSettings : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag BuffTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UTBPBaseBuff> BuffClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Duration = 3.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TickDeltaTime = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Value = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UNiagaraSystem* BuffVFX = nullptr;
};

UCLASS(Blueprintable, BlueprintType)
class TESTBUFFPROJECT_API UTBPBuffSystem : public UObject
{
    GENERATED_BODY()
	
public:

	void OnStartPlay();
	
	void ApplyBuffInRadius(UWorld* World, UTBPBaseBuff* Buff, const FVector& Location, float Radius) const;

	ATBPProjectile* SpawnProjectile(UWorld* World, ATBPBaseWeapon* Weapon, const FGameplayTag& BuffTag,
		const FVector& Location, const FVector& Direction) const;

	void SetProjectileParameters(ATBPProjectile* Projectile, const FGameplayTag& BuffTag) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Buff")
	UDataTable* BuffSettings = nullptr;
	
	UPROPERTY(Transient)
	TMap<FGameplayTag, FTBPBuffSettings> BuffSettingsMap;
};