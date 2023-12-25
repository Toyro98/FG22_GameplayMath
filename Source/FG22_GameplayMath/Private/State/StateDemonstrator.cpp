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

	float NewRotationInYaw = 0.0f;
	LocalContext = UContextHelpers::GetLocalContext(this);

	if (UContextHelpers::FlagPredicateLocal(LocalContext, ELocalContext::Hurt))
	{
		NewRotationInYaw = (360.0f / RotationsPerSecond) * DeltaTime;
	}
	else if (UContextHelpers::FlagPredicateLocal(LocalContext, ELocalContext::NearDeath))
	{
		NewRotationInYaw = (360.0f / RotationsPerSecond * 4.0f) * DeltaTime;
	}
	
	StaticMeshComponent->AddRelativeRotation(FRotator(0.0f, NewRotationInYaw, 0.0f));

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
		SetActorScale3D(FVector(FMath::FInterpConstantTo(CurrentScale, ScaleTo, DeltaTime, InterpolationScaleSpeed)));
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
}

bool AStateDemonstrator::ShouldTickIfViewportsOnly() const
{
	return true;
}
