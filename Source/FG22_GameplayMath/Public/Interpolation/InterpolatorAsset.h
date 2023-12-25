#pragma once

#include "CoreMinimal.h"
#include "Interpolator.h"
#include "Engine/DataAsset.h"
#include "InterpolatorAsset.generated.h"

UCLASS()
class FG22_GAMEPLAYMATH_API UInterpolatorAsset: public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FInterpolator Interpolator;
};
