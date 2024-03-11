// Test Buff Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TBPGameHUD.generated.h"

UCLASS()
class TESTBUFFPROJECT_API ATBPGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

private:
	void DrawCrossHair();	
};
