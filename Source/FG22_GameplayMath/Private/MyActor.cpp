#include "MyActor.h"

AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw debug arc
	const auto Location = GetActorLocation();
	const auto Cross = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());
	DrawDebugLine(GetWorld(), Location, Location + GetActorForwardVector() * 128.0f, FColor::Red, false, -1.0f, 0, 2);
	DrawDebugLine(GetWorld(), Location, Location + GetActorRightVector() * 128.0f, FColor::Green, false, -1.0f, 0, 2);
	DrawDebugLine(GetWorld(), Location, Location + Cross * 128.0f, FColor::Blue, false, -1.0f, 0, 2);

	if (TargetToCheck && TargetToCheck != this)
	{
		CheckDirectionTo(TargetToCheck);
	}
}

void AMyActor::CheckDirectionTo(const AMyActor* Target) const
{
	auto LocalSpaceLocation = GetActorTransform().InverseTransformPosition(Target->GetActorLocation());
	auto DebugText = FString::Printf(TEXT("%s is ("), *Target->GetActorNameOrLabel());

	if (LocalSpaceLocation.X > 0)
	{
		DebugText.Append(TEXT("in front "));
	}
	else if (LocalSpaceLocation.X < 0)
	{
		DebugText.Append(TEXT("behind "));
	}

	if (LocalSpaceLocation.Y > 0)
	{
		DebugText.Append(TEXT("| to the right"));
	}
	else if (LocalSpaceLocation.Y < 0)
	{
		DebugText.Append(TEXT("| to the left"));
	}

	if (LocalSpaceLocation.Z > 0)
	{
		DebugText.Append(TEXT("| above"));
	}
	else if (LocalSpaceLocation.Z < 0)
	{
		DebugText.Append(TEXT("| below"));
	}

	DebugText.Append(FString::Printf(TEXT(") of %s"), *GetActorNameOrLabel()));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Cyan, DebugText);
	}
}

