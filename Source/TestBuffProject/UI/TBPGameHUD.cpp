// Test Buff Project. All Rights Reserved.

#include "TBPGameHUD.h"
#include "Engine/Canvas.h"
#include "Math/Vector2D.h"

void ATBPGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void ATBPGameHUD::DrawCrossHair()
{
	const FVector2D Center(Canvas->SizeX*0.5f, Canvas->SizeY*0.5f);

	constexpr float HalfLineSize = 10.0f;
	constexpr float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Gray;
	
	DrawLine(Center.X - HalfLineSize, Center.Y, Center.X + HalfLineSize, Center.Y, LineColor, LineThickness);
	DrawLine(Center.X, Center.Y  - HalfLineSize, Center.X, Center.Y  + HalfLineSize, LineColor, LineThickness);
}