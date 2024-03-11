// Test Buff Project. All Rights Reserved.

#include "TBPHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UTBPHealthBarWidget::SetHealthPercent(float Percent)
{
	if (!HealthProgressBar)
	{
		return;
	}
	
    HealthProgressBar->SetPercent(Percent);
}
