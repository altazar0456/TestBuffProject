// Test Buff Project. All Rights Reserved.

#include "TBPHealthBarBuffWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UTBPHealthBarBuffWidget::SetHealthPercent(float Percent)
{
	if (!HealthProgressBar)
	{
		return;
	}
	
    HealthProgressBar->SetPercent(Percent);
}

void UTBPHealthBarBuffWidget::SetBuffStatus(FText BuffStatus)
{	
	if (!BuffStatusTextBlock)
	{
		return;
	}
	
	BuffStatusTextBlock->SetText(BuffStatus);
}