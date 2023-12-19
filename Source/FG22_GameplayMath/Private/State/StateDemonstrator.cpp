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

	if (UContextHelpers::FlagPredicateLocal(LocalContext, ELocalContext::Hurt))
	{
		StaticMeshComponent->AddRelativeRotation(
			FQuat::MakeFromRotator(FRotator(0, (360 / RotationsPerSecond) * DeltaTime, 0))
		);
	}
	else if (UContextHelpers::FlagPredicateLocal(LocalContext, ELocalContext::NearDeath))
	{
		StaticMeshComponent->AddRelativeRotation(
			FQuat::MakeFromRotator(FRotator(0, (360 / RotationsPerSecond * 2) * DeltaTime, 0))
		);
	}

	if (Demonstrator != nullptr)
	{
		RelativeContext = UContextHelpers::GetRelativeContext(Demonstrator, this);
		int32 BitMask = 0;

		SET_BIT(BitMask, ERelativeContext::InFront);
		SET_BIT(BitMask, ERelativeContext::ToTheRight);
		SET_BIT(BitMask, ERelativeContext::ToTheLeft);
		SET_BIT(BitMask, ERelativeContext::Above);
		SET_BIT(BitMask, ERelativeContext::Below);
		SET_BIT(BitMask, ERelativeContext::Close);
		SET_BIT(BitMask, ERelativeContext::Seen);

		const float CurrentScale = StaticMeshComponent->GetComponentScale().X;
		const float ScaleTo = UContextHelpers::ContextPredicate(BitMask, RelativeContext) ? MaxScale : MinScale;
		SetActorScale3D(FVector(FMath::FInterpConstantTo(CurrentScale, ScaleTo, DeltaTime, InterpolationSpeed)));
	}

	if (DrawCone)
	{
		DrawDebugCone(
			GetWorld(), 
			StaticMeshComponent->GetComponentLocation(), 
			StaticMeshComponent->GetForwardVector(), 
			CONTEXT_RANGE, 
			FMath::DegreesToRadians(CONTEXT_ANGLE), 
			0.0f, 
			1, 
			FColor::Green
		);
	}

	if (DrawConnectingLine && Demonstrator != nullptr)
	{
		DrawDebugLine(
			GetWorld(), 
			StaticMeshComponent->GetComponentLocation(),
			Demonstrator->GetActorLocation(), 
			FColor::Blue
		);
	}
}

bool AStateDemonstrator::ShouldTickIfViewportsOnly() const
{
	return true;
}
