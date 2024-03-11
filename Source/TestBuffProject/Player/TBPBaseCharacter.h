// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TBPBaseCharacter.generated.h"

class UTBPWeaponComponent;

UCLASS()
class TESTBUFFPROJECT_API ATBPBaseCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ATBPBaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTBPWeaponComponent* WeaponComponent = nullptr;
	
	virtual void BeginPlay();
	
	virtual void OnDeath();
};
