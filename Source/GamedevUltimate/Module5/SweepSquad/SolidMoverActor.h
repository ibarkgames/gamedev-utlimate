// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolidMoverActor.generated.h"

// Goal: Learn how to use the bSweep parameter while making an Actor move.
// Remember how your Module 2 movement Actors happily flew through every wall? Time to fix that.
// Create an Actor that moves forwards on every Tick using the AddActorLocalOffset function (or AddActorWorldOffset).
// The function has a bSweep parameter, set it to true and pass in an FHitResult.
// Play the game and watch the Actor stop at the first wall instead of ghosting through it.
// Set bSweep to false and observe the difference.
// Bonus: When the Actor hits a wall, reverse its movement direction. You just built the Distance Based
// Movement exercise from Module 2 without needing any distance threshold.

class UArrowComponent;
UCLASS()
class GAMEDEVULTIMATE_API ASolidMoverActor : public AActor
{
	GENERATED_BODY()

public:
	ASolidMoverActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "SolidMoverActor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "SolidMoverActor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> ArrowComponent;

	UPROPERTY(EditAnywhere, Category = "SolidMoverActor", meta = (AllowPrivateAccess = "true"))
	float Speed{ 100.f };

	UPROPERTY(EditAnywhere, Category = "SolidMoverActor", meta = (AllowPrivateAccess = "true"))
	bool bSweep{ true };
};
