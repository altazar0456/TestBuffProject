// Test Buff Project. All Rights Reserved.

#include "TBPProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Health/TBPHealthComponent.h"
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
	if(!GetWorld())
	{
		return;
	}

	MovementComponent->StopMovementImmediately();

	//TODO: replace code nearby - Make buff to all characters nearby
	//TODO: use interfaces
	ATBPBaseCharacter* Character = Cast<ATBPBaseCharacter>(Actor);
	if(Character)
	{
		Character->HealthComponent->ApplyDamage(20.0f);
	}
	// TODO: End TODO:

	Destroy();
}
