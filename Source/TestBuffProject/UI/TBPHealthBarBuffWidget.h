// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TBPHealthBarBuffWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class TESTBUFFPROJECT_API UTBPHealthBarBuffWidget : public UUserWidget
{
    GENERATED_BODY()
	
public:
    void SetHealthPercent(float Percent);
    void SetBuffStatus(FText BuffStatus);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BuffStatusTextBlock;	
};
