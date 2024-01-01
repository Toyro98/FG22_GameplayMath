#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/PointLight.h"
#include "MyLightActor.generated.h"

UCLASS(HideCategories = (Input, Movement, Collision, Rendering, HLOD, WorldPartition, DataLayers, Replication, Physics, Networking, Actor, LevelInstance, Cooking))
class FG22_GAMEPLAYMATH_API AMyLightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyLightActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FLinearColor> Colors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Index;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PreviousIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APointLight* LightActor;
};
