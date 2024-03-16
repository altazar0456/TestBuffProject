// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TBPBaseCharacter.generated.h"

class UTextBlock;
class UTBPHealthComponent;
class UTBPWeaponComponent;
class UWidgetComponent;
class UTBPBuffSystemComponent;

UCLASS()
class TESTBUFFPROJECT_API ATBPBaseCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ATBPBaseCharacter(const FObjectInitializer& ObjInit);

	//TODO: Move to protected
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTBPHealthComponent* HealthComponent;
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTBPWeaponComponent* WeaponComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthBuffWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTBPBuffSystemComponent* BuffSystemComponent;
	
	virtual void BeginPlay() override;
	
	void OnDeath();
    void OnHealthChanged(float Health);
	
	void OnBuffChanged(FText Health);
};
