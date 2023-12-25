#pragma once

#include "CoreMinimal.h"
#include "InterpObject.h"

class FCurveDuration final : public FInterpObject
{
	UCurveFloat* Curve;

public:
	FCurveDuration(const float Duration, UCurveFloat* Curve): FInterpObject(Duration)
	{
		this->Curve = Curve;
	}

	virtual void Update(const float DeltaTime) override
	{
		FInterpObject::Update(DeltaTime);
		CurrentValue = Curve->FloatCurve.Eval(T);
	}
};