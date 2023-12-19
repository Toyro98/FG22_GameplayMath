#pragma once

// Check if a mask has a single flag
#define TEST_BIT(Bitmask, Bit) (((Bitmask) & (1 << static_cast<int32>(Bit))) > 0)

// Check if a mask contains another mask
#define TEST_BITS(Bitmask, Bits) (((Bitmask) & Bits) == Bits)

// Set a specific bit
#define SET_BIT(Bitmask, Bit) (Bitmask |= 1 << static_cast<int32>(Bit))

// Clear a specific bit
#define CLEAR_BIT(Bitmask, Bit)	(Bitmask &= ~(1 << static_cast<int32>(Bit)))

#include "CoreMinimal.h"
#include "LocalContext.h"
#include "RelativeContext.h"
#include "../State/StateDemonstrator.h"
#include "../Constants.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ContextHelpers.generated.h"

UCLASS()
class FG22_GAMEPLAYMATH_API UContextHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Context", meta = (DefaultToSelf = Target))
	static int32 GetLocalContext(const AActor* Target)
	{
		int32 ReturnContext = 0;
		const auto StateDemonstrator = Cast<AStateDemonstrator>(Target);

		if (!StateDemonstrator)
		{
			return ReturnContext;
		}

		const float Health = StateDemonstrator->Health;
		if (Health < CONTEXT_DYING_THRESHOLD)
		{
			SET_BIT(ReturnContext, ELocalContext::NearDeath);
		}
		else if (Health < CONTEXT_HURT_THRESHOLD)
		{
			SET_BIT(ReturnContext, ELocalContext::Hurt);
		}

		return ReturnContext;
	}

	UFUNCTION(BlueprintCallable, Category = "Context", meta = (DefaultToSelf = Target))
	static int32 GetRelativeContext(const AActor* Target, const AActor* Other)
	{
		int32 ReturnContext = 0;

		const auto TargetLocation = Target->GetActorLocation();
		const auto OtherLocation = Other->GetActorLocation();
		const auto Direction = OtherLocation - TargetLocation;

		const auto LocalSpaceLocation = Target->GetActorTransform().InverseTransformPosition(OtherLocation);

		if (LocalSpaceLocation.X > 0)
		{
			SET_BIT(ReturnContext, ERelativeContext::InFront);
		}
		else if (LocalSpaceLocation.X < 0)
		{
			SET_BIT(ReturnContext, ERelativeContext::Behind);
		}

		if (LocalSpaceLocation.Y > 0)
		{
			SET_BIT(ReturnContext, ERelativeContext::ToTheRight);
		}
		else if (LocalSpaceLocation.Y < 0)
		{
			SET_BIT(ReturnContext, ERelativeContext::ToTheLeft);
		}

		if (LocalSpaceLocation.Z > 0)
		{
			SET_BIT(ReturnContext, ERelativeContext::Above);
		}
		else if (LocalSpaceLocation.Z < 0)
		{
			SET_BIT(ReturnContext, ERelativeContext::Below);
		}

		const float Distance = Direction.Length();
		if (Distance > CONTEXT_RANGE)
		{
			SET_BIT(ReturnContext, ERelativeContext::Far);
		}
		else
		{
			SET_BIT(ReturnContext, ERelativeContext::Close);
		}

		const float Angle = FindAngle(Target->GetActorForwardVector(), Direction.GetSafeNormal());
		const float HalfGlobalAngle = CONTEXT_ANGLE;
		if (Angle < HalfGlobalAngle && Angle > -HalfGlobalAngle)
		{
			SET_BIT(ReturnContext, ERelativeContext::Seen);
		}
		else
		{
			SET_BIT(ReturnContext, ERelativeContext::Unseen);
		}

		const double FacingDot = FVector::DotProduct(Target->GetActorForwardVector(), Other->GetActorForwardVector());
		if (FacingDot > CONTEXT_DIRECTION_THRESHOLD)
		{
			SET_BIT(ReturnContext, ERelativeContext::FacingSame);
		}
		else if (FacingDot < -CONTEXT_DIRECTION_THRESHOLD)
		{
			SET_BIT(ReturnContext, ERelativeContext::FacingOpposite);
		}

		return ReturnContext;
	}

	UFUNCTION(BlueprintCallable, Category = "Context")
	static float FindAngle(const FVector SelfForward, const FVector TargetForward)
	{
		double Dot = FVector::DotProduct(SelfForward, TargetForward);
		Dot = FMath::Clamp(Dot, -1.0f, 1.0f);
		return FMath::RadiansToDegrees(FMath::Acos(Dot));
	}

	// Used for checking a group of flags
	UFUNCTION(BlueprintCallable, Category = "Context")
	static bool ContextPredicate(const int32 BitMask, const int32 Bits)
	{
		return TEST_BITS(BitMask, Bits);
	}

	// Used for checking a single local flag 
	UFUNCTION(BlueprintCallable, Category = "Context")
	static bool FlagPredicateLocal(const int32 BitMask, const ELocalContext Bit)
	{
		return TEST_BIT(BitMask, Bit);
	}
	
	// Used for checking a single relative flag
	UFUNCTION(BlueprintCallable, Category = "Context")
	static bool FlagPredicateRelative(const int32 BitMask, const ERelativeContext Bit)
	{
		return TEST_BIT(BitMask, Bit);
	}
};
