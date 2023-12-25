#include "Interpolation/InterpolationDemonstrator.h"

AInterpolationDemonstrator::AInterpolationDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInterpolationDemonstrator::BeginPlay()
{
	Super::BeginPlay();
	Interpolator->Interpolator.Initialize();
	Origin = GetActorLocation();
}

void AInterpolationDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO
}