#include "MyNoiseActor.h"

AMyNoiseActor::AMyNoiseActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyNoiseActor::BeginPlay()
{
	Super::BeginPlay();

	Triangles.SetNum(Size * Size * NUM_TRIANGLES);
	Vertices.SetNum((Size + 1) * (Size + 1));

	for (int32 x = 0, i = 0; x <= Size; x++)
	{
		for (int32 y = 0; y <= Size; y++, i++)
		{
			float z = FMath::PerlinNoise2D(FVector2D(x * HeightStrength, y * HeightStrength)) * UE_PI;
			Vertices[i] = FVector(x * QuadSize, y * QuadSize, z * QuadSize / 2);
		}
	}

	int32 Vertex = 0;
	int32 TriangleCount = 0;
	for (int32 x = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{
			Triangles[TriangleCount] = Vertex;
			Triangles[TriangleCount + 1] = Vertex + Size + 1;
			Triangles[TriangleCount + 2] = Vertex + 1;
			Triangles[TriangleCount + 3] = Vertex + Size + 2;

			Vertex++;
			TriangleCount += NUM_TRIANGLES;
		}

		Vertex++;
	}
}

void AMyNoiseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 x = 0, i = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{
			int32 BottomLeft = Triangles[i + 0];
			int32 TopLeft = Triangles[i + 1];
			int32 BottomRight = Triangles[i + 2];
			int32 TopRight = Triangles[i + 3];

			// Bottom Left -> Top Left
			DrawDebugLine(GetWorld(), Vertices[BottomLeft], Vertices[TopLeft], Color, false, 0.0f);

			// Top Left -> Bottom Right
			DrawDebugLine(GetWorld(), Vertices[TopLeft], Vertices[BottomRight], Color, false, 0.0f);

			// Bottom Right -> Bottom Left
			DrawDebugLine(GetWorld(), Vertices[BottomRight], Vertices[BottomLeft], Color, false, 0.0f);

			// Top Left -> Top Right
			DrawDebugLine(GetWorld(), Vertices[TopLeft], Vertices[TopRight], Color, false, 0.0f);

			// Top Right -> Bottom Right
			DrawDebugLine(GetWorld(), Vertices[TopRight], Vertices[BottomRight], Color, false, 0.0f);

			/* Not needed as the 2nd drawdebugline draws the diagonal line
			// Bottom Right -> Top Left
			DrawDebugLine(GetWorld(), Vertices[BottomRight], Vertices[TopLeft], FColor::White, false, 0.0f);
			*/

			i += NUM_TRIANGLES;
		}
	}
}
