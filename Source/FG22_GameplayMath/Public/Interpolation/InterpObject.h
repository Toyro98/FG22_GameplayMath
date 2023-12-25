#pragma once

class FInterpObject
{
	float Time = 0.0f;

protected:
	float Duration = 0.0f;
	float CurrentValue = 0.0f;
	float T = 0.0f;

public:
	FInterpObject(const float Duration)
	{
		this->Duration = Duration;
		Time = 0.0f;
	}

	virtual void Update(const float DeltaTime)
	{
		Time += DeltaTime;
		Time = FMath::Clamp(Time, 0.0f, Duration);
		T = Time / Duration;
	}

	float GetValue() const
	{
		return CurrentValue;
	}

	void Reset()
	{
		Time = 0.0f;
	}
};