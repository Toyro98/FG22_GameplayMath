#include "State/StateDemonstrator.h"
#include "Context/ContextHelpers.h"

AStateDemonstrator::AStateDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AStateDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LocalContext = UContextHelpers::GetLocalContext(this);
	int32 BitMask = 0;

	SET_BIT(BitMask, ELocalContext::Hurt);

	if (UContextHelpers::ContextPredicate(BitMask, LocalContext))
	{
		// Tried with the bit, could not get it to work. FlagPredicate doesn't seem to work? Might have used it wrong
		if (Health < CONTEXT_HURT_THRESHOLD)
		{
			const int32 RotationsPerSecond = 6;
			StaticMeshComponent->AddRelativeRotation(FQuat::MakeFromRotator(FRotator(0, (360 / RotationsPerSecond) * DeltaTime, 0)));
		}
	}

	if (Demonstrator != nullptr)
	{
		RelativeContext = UContextHelpers::GetRelativeContext(Demonstrator, this);
		BitMask = 0;

		// Using SET_BIT macro instead of setting it to a specific value. Makes it easier to make changes too
		SET_BIT(BitMask, ERelativeContext::Close);
		SET_BIT(BitMask, ERelativeContext::InFront);
		SET_BIT(BitMask, ERelativeContext::ToTheRight);
		SET_BIT(BitMask, ERelativeContext::ToTheLeft);
		SET_BIT(BitMask, ERelativeContext::Above);
		SET_BIT(BitMask, ERelativeContext::Below);
		SET_BIT(BitMask, ERelativeContext::Seen);

		// Couldn't think of anything better example to use
		if (UContextHelpers::ContextPredicate(BitMask, RelativeContext))
		{
			SetActorScale3D(FVector(1.0f));
		}
		else
		{
			SetActorScale3D(FVector(0.5f));
		}
	}

	if (DrawCone)
	{
		DrawDebugCone(GetWorld(), StaticMeshComponent->GetComponentLocation(), StaticMeshComponent->GetForwardVector(), CONTEXT_RANGE, FMath::DegreesToRadians(CONTEXT_ANGLE), 0.0f, 1, FColor::Green);
	}

	if (DrawConnectingLine && Demonstrator != nullptr)
	{
		DrawDebugLine(GetWorld(), StaticMeshComponent->GetComponentLocation(), Demonstrator->GetActorLocation(), FColor::Blue);
	}
}

bool AStateDemonstrator::ShouldTickIfViewportsOnly() const
{
	return true;
}
