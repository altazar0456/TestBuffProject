// Test Buff Project. All Rights Reserved.

#include "TBPHealthComponent.h"

UTBPHealthComponent::UTBPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UTBPHealthComponent::GetHealth() const
{
	return Health;
}

float UTBPHealthComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void UTBPHealthComponent::BeginPlay()
{
    Super::BeginPlay();
	
	check(MaxHealth > 0);

	SetHealth(MaxHealth);
}

void UTBPHealthComponent::ApplyDamage(float Damage)
{	
	if (Damage <= 0.0f || IsDead() || !GetWorld())
	{
		return;
	}
	
	SetHealth(Health - Damage);
	
	if (IsDead())
	{
        OnDeath.Broadcast();
	}
}

bool UTBPHealthComponent::IsDead() const
{
	return FMath::IsNearlyZero(Health);
}

void UTBPHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}