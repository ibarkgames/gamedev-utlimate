// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SweepVsTraceActor.generated.h"

// Goal: Visualizing the differences between a shape sweep and a line trace.
// Create an Actor that shoots a line trace and a sphere sweep at the same time, in the same direction.
// Visualize the line trace with a DebugLine from the start to the end.
// Draw the line in red color if nothing is hitting.
// Draw the line in green color if there is a hit.
// Visualize the shape sweep with DebugSpheres.
// Draw 2 debug spheres, one at the start of the sweep and one at the end of the sweep.
// If there is a hit draw another debug sphere at the Hit Location.
// Place a small object in front of the Actor, slightly off to the side, so it's not perfectly centered.
// Play the game and observe: the line misses it, the sweep catches it.
// Try to answer this question: When would you prefer a sweep over a line trace? Think about a melee attack or a thick
// projectile.

UCLASS()
class GAMEDEVULTIMATE_API ASweepVsTraceActor : public AActor
{
	GENERATED_BODY()

public:
	ASweepVsTraceActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "SweepVsTraceActor", meta = (AllowPrivateAccess = true))
	float TraceLength{ 1000.f };

	UPROPERTY(EditAnywhere, Category = "SweepVsTraceActor", meta = (AllowPrivateAccess = true))
	float SweepRadius{ 50.f };
};
