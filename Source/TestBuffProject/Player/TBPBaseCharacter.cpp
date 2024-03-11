// Test Buff Project. All Rights Reserved.

#include "TBPBaseCharacter.h"
#include "Health/TBPHealthComponent.h"
#include "Weapon/TBPWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/TBPHealthBarWidget.h"

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
	
	HealthComponent = CreateDefaultSubobject<UTBPHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UTBPWeaponComponent>("WeaponComponent");
	
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ATBPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(WeaponComponent);
	check(GetCharacterMovement());
	check(GetCapsuleComponent());
	check(GetMesh());
	
	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ATBPBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ATBPBaseCharacter::OnHealthChanged);
}

void ATBPBaseCharacter::OnDeath()
{
	UE_LOG(LogTemp, Display, TEXT("%s is dead"), *GetName());
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();
	HealthWidgetComponent->SetVisibility(false, true);
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void ATBPBaseCharacter::OnHealthChanged(float Health)
{	
	const auto HealthBarWidget = Cast<UTBPHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget) return;
	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}