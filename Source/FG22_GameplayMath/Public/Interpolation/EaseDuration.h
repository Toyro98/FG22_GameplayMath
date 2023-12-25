#pragma once

#include "InterpObject.h"
#include "Easing/EasingFunctions.h"

class FEaseDuration final: public FInterpObject
{
	EEasingType Type;

public:
	FEaseDuration(const float Duration, const EEasingType Type): FInterpObject(Duration)
	{
		this->Type = Type;
	}

	virtual void Update(const float DeltaTime) override
	{
		FInterpObject::Update(DeltaTime);
		CurrentValue = UEasingFunctions::GetEaseValue(Type, T);
	}
};