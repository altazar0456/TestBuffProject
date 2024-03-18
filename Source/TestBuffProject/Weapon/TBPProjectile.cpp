// Test Buff Project. All Rights Reserved.

#include "TBPProjectile.h"

#include "DrawDebugHelpers.h"
#include "TBPBaseGameMode.h"
#include "Buff/TBPBuffSystem.h"
#include "Buff/TBPMovementSpeedModifierBuff.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TBPBaseCharacter.h"

ATBPProjectile::ATBPProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;
}

void ATBPProjectile::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->OnComponentHit.AddDynamic(this, &ATBPProjectile::OnProjectileHit);
	SetLifeSpan(5.0f);
}

void ATBPProjectile::SetShotDirection(const FVector& Direction)
{
	ShotDirection = Direction;
}

void ATBPProjectile::OnProjectileHit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, FVector Vector, const FHitResult& HitResult)
{
	MovementComponent->StopMovementImmediately();

	const ATBPBaseGameMode* GameMode = Cast<ATBPBaseGameMode>(UGameplayStatics::GetGameMode(this));
	check(GameMode);
	check(GameMode->BuffSystem);
	check(GetWorld())
	
	if(Buff)
	{
		GameMode->BuffSystem->ApplyBuffInRadius(GetWorld(), Buff, HitResult.ImpactPoint, Radius);
		
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, Radius, 32, FColor::Orange, false, 3.0f, 0, 3.0f);
	}

	Destroy();
}