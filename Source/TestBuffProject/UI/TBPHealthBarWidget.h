// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TBPHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class TESTBUFFPROJECT_API UTBPHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()
	
public:
    void SetHealthPercent(float Percent);
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;
};
