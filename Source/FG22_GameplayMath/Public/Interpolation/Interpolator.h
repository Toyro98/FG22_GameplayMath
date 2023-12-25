#pragma once

//#include "GameFramework/Actor.h"
#include "EaseDuration.h"
#include "InterpType.h"
#include "InterpObject.h"
#include "CurveDuration.h"
#include "LerpDuration.h"
#include "Interpolator.generated.h"

USTRUCT(Blueprintable)
struct FInterpolator
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Duration = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EInterpType> Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EEasingType> EasingType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* CurveFloat = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float From = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float To = 0.0f;

	void Initialize()
	{
		switch (Type)
		{
		case EInterpType::EasingFunction:
			Instance = new FEaseDuration(Duration, EasingType);
			break;
		case EInterpType::Curve:
			Instance = new FCurveDuration(Duration, CurveFloat);
			break;
		default: case EInterpType::Lerp:
			Instance = new FLerpDuration(Duration, From, To);
			break;
		}
	}

	void Update(const float DeltaTime) const
	{
		Instance->Update(DeltaTime);
	}

	float GetValue() const
	{
		return Instance->GetValue();
	}

	void Reset() const
	{
		Instance->Reset();
	}

private:
	FInterpObject* Instance = nullptr;
};