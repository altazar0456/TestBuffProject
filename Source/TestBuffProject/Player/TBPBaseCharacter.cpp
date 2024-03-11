// Test Buff Project. All Rights Reserved.

#include "TBPBaseCharacter.h"
#include "Weapon/TBPWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ATBPBaseCharacter::ATBPBaseCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	WeaponComponent = CreateDefaultSubobject<UTBPWeaponComponent>("WeaponComponent");
}

void ATBPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponComponent);
	check(GetCharacterMovement());
	check(GetCapsuleComponent());
	check(GetMesh());
}

//TODO: Add callback from health component
void ATBPBaseCharacter::OnDeath()
{
	UE_LOG(LogTemp, Display, TEXT("%s is dead"), *GetName());
}