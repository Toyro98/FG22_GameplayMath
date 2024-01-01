#include "MyLightActor.h"

AMyLightActor::AMyLightActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyLightActor::BeginPlay()
{
	Super::BeginPlay();

	Colors.Add(FLinearColor(1.0f, 0.0f, 0.0f));
	Colors.Add(FLinearColor(1.0f, 0.5f, 0.0f));
	Colors.Add(FLinearColor(1.0f, 1.0f, 0.0f));
	Colors.Add(FLinearColor(0.5f, 1.0f, 0.0f));
	Colors.Add(FLinearColor(0.0f, 1.0f, 0.0f));
	Colors.Add(FLinearColor(0.0f, 1.0f, 0.5f));
	Colors.Add(FLinearColor(0.0f, 1.0f, 1.0f));
	Colors.Add(FLinearColor(0.0f, 0.5f, 1.0f));
	Colors.Add(FLinearColor(0.0f, 0.0f, 1.0f));
	Colors.Add(FLinearColor(0.5f, 0.0f, 1.0f));
	Colors.Add(FLinearColor(1.0f, 0.0f, 1.0f));
	Colors.Add(FLinearColor(1.0f, 0.0f, 0.5f));
}

void AMyLightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!LightActor)
	{
		return;
	}

	Time += DeltaTime / Duration;
	Time = FMath::Clamp(Time, 0.0f, 1.0f);

	FLinearColor StartColor = Colors[PreviousIndex];
	FLinearColor EndColor = Colors[Index];

	LightActor->SetLightColor(FMath::Lerp(StartColor, EndColor, Time));

	if (Time >= 1.0f)
	{
		PreviousIndex = Index;
		Index = (Index + 1) % Colors.Num();
		Time = 0.0f;
	}
}

