// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "ShapeShiftingActor.h"
#include "GameFramework/Actor.h"
#include "RotatedSweepActor.generated.h"

// Goal: Learn how to rotate the shape of the sweep.
// Remember the FQuat::Identity rotation parameter from the first exercise? Time to use it.
// Create an Actor that sweeps a box shape forwards.
// Add an ArrowComponent to the Actor, you're going to use this for the sweep rotation.
// Draw a debug box with the correct rotation so you can see what's happening.
// First pass FQuat::Identity, then pass the ArrowComponent's rotation. (GetComponentQuat)
// Rotate the ArrowComponent in the editor and observe the difference between the two versions.
// Try to answer this question: Does the rotation parameter matter when sweeping a sphere?

class UArrowComponent;
UCLASS()
class GAMEDEVULTIMATE_API ARotatedSweepActor : public AActor
{
	GENERATED_BODY()

public:
	ARotatedSweepActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "RotatedSweepActor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> ArrowComponent;

	UPROPERTY(EditAnywhere, Category = "RotatedSweepActor", meta = (AllowPrivateAccess = "true"))
	float SweepLength{ 1000.f };

	UPROPERTY(EditAnywhere, Category = "RotatedSweepActor", meta = (AllowPrivateAccess = "true"))
	FBoxShapeParams BoxShapeParams;
};
