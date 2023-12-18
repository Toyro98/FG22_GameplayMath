#pragma once

UENUM(BlueprintType, Meta = (Bitflags))
enum class ERelativeContext : uint8
{
	None,
	Behind,
	InFront,
	ToTheRight,
	ToTheLeft,
	Above,
	Below,
	Close,
	Far,
	Seen,
	Unseen,
	FacingSame,
	FacingOpposite
};