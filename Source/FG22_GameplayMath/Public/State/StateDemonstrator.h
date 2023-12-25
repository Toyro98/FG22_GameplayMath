#pragma once

#include "CoreMinimal.h"
#include "Demonstrator.h"
#include "../Constants.h"
#include "StateDemonstrator.generated.h"

UCLASS()
class FG22_GAMEPLAYMATH_API AStateDemonstrator : public ADemonstrator
{
	GENERATED_BODY()

public:
	AStateDemonstrator();

	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	float MinScale = 0.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	float MaxScale = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	float InterpolationScaleSpeed = 1.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State", Meta = (UIMin = 0.0f, UIMax = 1.0f, ClampMin = 0.0f, ClampMax = 1.0f))
	float Health = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	float RotationsPerSecond = 4.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Context", Meta = (Bitmask, BitmaskEnum = "/Script/FG22_GameplayMath.ELocalContext"))
	int32 LocalContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Context", Meta = (Bitmask, BitmaskEnum = "/Script/FG22_GameplayMath.ERelativeContext"))
	int32 RelativeContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Context")
	AActor* Demonstrator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
	bool DrawCone;
};
