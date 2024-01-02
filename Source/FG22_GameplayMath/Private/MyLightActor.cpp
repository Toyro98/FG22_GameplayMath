#include "MyLightActor.h"

AMyLightActor::AMyLightActor()
{
	PrimaryActorTick.bCanEverTick = true;

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

void AMyLightActor::BeginPlay()
{
	Super::BeginPlay();
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

	FLinearColor CurrentColor = FMath::Lerp(Colors[PreviousIndex], Colors[Index], Time);
	LightActor->SetLightColor(CurrentColor);

	if (Time >= 1.0f)
	{
		PreviousIndex = Index;
		Index = (Index + 1) % Colors.Num();
		Time = 0.0f;
	}
}

