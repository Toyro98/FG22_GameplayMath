#pragma once

#include "CoreMinimal.h"
#include "InterpObject.h"

class FLerpDuration final : public FInterpObject
{
	float From;
	float To;

public:
	FLerpDuration(const float Duration, const float From, const float To): FInterpObject(Duration)
	{
		this->From = From;
		this->To = To;
	}

	virtual void Update(const float DeltaTime) override
	{
		FInterpObject::Update(DeltaTime);
		CurrentValue = FMath::Lerp(From, To, T);
	}
};