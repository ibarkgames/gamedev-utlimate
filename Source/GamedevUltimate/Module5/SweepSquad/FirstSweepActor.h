// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstSweepActor.generated.h"

// Goal: Create an Actor that sweeps a sphere forwards on every Tick.
// The sweep should start at the Actor's location and end 1000 units in front of it.
// Use the SweepSingleByChannel function with the ECC_Visibility channel.
// Pass FQuat::Identity for the rotation parameter, we will get to that later.
// Create the sphere shape using FCollisionShape::MakeSphere with a radius of 50.
// If the sweep hits something, log the name of the hit Actor to the screen.
// Draw a debug line for the sweep path.
// Draw 2 debug spheres, one at the start of the sweep and one at the end of the sweep.
// Debug spheres should have the same radius as the sphere shape you created for the sweep!
// Place the Sweep Actor in the level, place moving objects in front of it.
// Observe how the sweep hits the objects, it covers a larger volume compared to a line trace.

// Goal: Understanding the difference between the Hit Location and Impact Point.
// Continue with the Actor from the previous exercise.
// The FHitResult of a sweep has 2 important members that are NOT the same: Location and ImpactPoint.
// Log both of them to the screen and compare the values.
// Draw a debug sphere with your sweep radius at the Location of the hit.
// Draw a very small debug sphere at the ImpactPoint of the hit.
// Observe the difference:
// Location is where the swept shape was when it touched something.
// Impact Point is the exact touch point on the surface.
// Try to answer this question: Which one would you use to safely place an object next to a wall, without clipping into
// it?

class UTextRenderComponent;

UCLASS()
class GAMEDEVULTIMATE_API AFirstSweepActor : public AActor
{
	GENERATED_BODY()

public:
	AFirstSweepActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = FirstSweepActor, meta = (AllowPrivateAccess = true))
	float SweepLength{ 1000.f };

	UPROPERTY(EditAnywhere, Category = FirstSweepActor, meta = (AllowPrivateAccess = true))
	float SweepRadius{ 50.f };

	UPROPERTY(EditDefaultsOnly, Category = FirstSweepActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;

	UPROPERTY(VisibleAnywhere, Category = FirstSweepActor, meta = (AllowPrivateAccess = true))
	FTimerHandle TextTimer;

	UPROPERTY(EditAnywhere, Category = FirstSweepActor, meta = (AllowPrivateAccess = true))
	float TextDuration{ 3.f };
};
