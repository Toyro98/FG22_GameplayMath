#pragma once

#include "CoreMinimal.h"
#include "Demonstrator.h"
#include "Interpolator.h"
#include "InterpolatorAsset.h"
#include "InterpolationDemonstrator.generated.h"

UCLASS()
class FG22_GAMEPLAYMATH_API AInterpolationDemonstrator : public ADemonstrator
{
	GENERATED_BODY()

	FVector Origin;
	FVector Goal;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInterpolatorAsset* Interpolator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetPosition;

public:
	AInterpolationDemonstrator();
	virtual void Tick(float DeltaTime) override;
};
