#pragma once

UENUM(BlueprintType, Meta = (Bitflags))
enum class ELocalContext : uint8
{
	None,
	Hurt,
	NearDeath,
	Terrified,
	Scared,
	Spooked,
};