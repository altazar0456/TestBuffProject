// Test Buff Project. All Rights Reserved.

#include "TBPPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/TBPWeaponComponent.h"


ATBPPlayerCharacter::ATBPPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}


void ATBPPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATBPPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATBPPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATBPPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATBPPlayerCharacter::LookUpAtRate);	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATBPPlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UTBPWeaponComponent::StopFire);
	
	DECLARE_DELEGATE_OneParam(FEquipWeaponSignature, int32);
	PlayerInputComponent->BindAction<FEquipWeaponSignature>("EquipWeapon1", IE_Pressed, WeaponComponent, &UTBPWeaponComponent::EquipWeapon, 0);
	PlayerInputComponent->BindAction<FEquipWeaponSignature>("EquipWeapon2", IE_Pressed, WeaponComponent, &UTBPWeaponComponent::EquipWeapon, 1);
	PlayerInputComponent->BindAction<FEquipWeaponSignature>("EquipWeapon3", IE_Pressed, WeaponComponent, &UTBPWeaponComponent::EquipWeapon, 2);
}

void ATBPPlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATBPPlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATBPPlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATBPPlayerCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATBPPlayerCharacter::StartFire()
{
	check(WeaponComponent);
	
	WeaponComponent->StartFire();
}