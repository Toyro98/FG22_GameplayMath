#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyNoiseActor.generated.h"

#define NUM_TRIANGLES 4

UCLASS(HideCategories = (Input, Movement, Collision, Rendering, HLOD, WorldPartition, DataLayers, Replication, Physics, Networking, Actor, LevelInstance, Cooking))
class FG22_GAMEPLAYMATH_API AMyNoiseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyNoiseActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Size = 64;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeightStrength = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float QuadSize = 128.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color = FColor::White;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FVector> Vertices;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int32> Triangles;
};
