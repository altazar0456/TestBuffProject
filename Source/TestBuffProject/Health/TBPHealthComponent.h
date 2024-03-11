// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TBPHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS()
class TESTBUFFPROJECT_API UTBPHealthComponent : public UActorComponent
{
    GENERATED_BODY()
	
public:
	UTBPHealthComponent();
	
	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;
	
	float GetHealth() const;
	float GetHealthPercent() const;

	void ApplyDamage(float Damage);
    bool IsDead() const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;
	
	virtual void BeginPlay() override;
	
    void SetHealth(float NewHealth);
	
private:
	float Health = 0.0f;
};
