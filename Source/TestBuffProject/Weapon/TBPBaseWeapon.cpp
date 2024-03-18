// Test Buff Project. All Rights Reserved.

#include "TBPBaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "TBPBaseGameMode.h"
#include "TBPProjectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ATBPBaseWeapon::ATBPBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
	
	ProjectileClass = ATBPProjectile::StaticClass();
}

void ATBPBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

void ATBPBaseWeapon::StartFire()
{
	bFireInProgress = true;
}

void ATBPBaseWeapon::StopFire()
{
	bFireInProgress = false;
}

bool ATBPBaseWeapon::IsFiring() const
{
	return bFireInProgress;
}

void ATBPBaseWeapon::MakeShot()
{
	UE_LOG(LogTemp, Log, TEXT("Shot projectile from Launcher weapon"));
	
	FVector TraceStart;
	FVector TraceEnd;
	if(GetProjectileTraceData(TraceStart, TraceEnd))
	{		
		const ATBPBaseGameMode* GameMode = Cast<ATBPBaseGameMode>(UGameplayStatics::GetGameMode(this));
		check(GameMode);
		
		const FVector Direction = (TraceEnd - TraceStart).GetSafeNormal();
		
		GameMode->BuffSystem->SpawnProjectile(GetWorld(), this, BuffTag, TraceStart, Direction);
	}
}

bool ATBPBaseWeapon::GetProjectileTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	UWorld* World = GetWorld();
	ACharacter* Player = Cast<ACharacter>(GetOwner());
	APlayerController* Controller = Player ? Player->GetController<APlayerController>() : nullptr;
	if(!World || !Player || !Controller)
	{
		return false;
	}
	
	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	
	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStartCamera = ViewLocation;
	TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = ViewRotation.Vector();
	const FVector CameraTraceEnd = TraceStartCamera + ShootDirection * TraceMaxDistance;
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	World->LineTraceSingleByChannel(HitResult, TraceStartCamera, CameraTraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

	if(HitResult.bBlockingHit)
	{
		TraceEnd = HitResult.ImpactPoint;
	}
	else
	{
		TraceEnd = CameraTraceEnd;
	}
	
	return true;
}