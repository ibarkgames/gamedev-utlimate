// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstTraceActor.generated.h"

// Goal: Create an Actor that shoots a line trace forwards on every Tick.
// Use the LineTraceSingleByChannel function with the ECC_Visibility channel.
// The trace should start at the Actor's location.
// The trace should end 1000 units in front of the Actor.
// The trace function returns a bool that tells you if something was hit.
// If the trace hits something, log a message to the screen: "Trace hit something!".
// Draw a debug line from the start to the end of the trace so you can see it.
// A red line when the trace hits something, green line when it doesn't.
// Place the Actor in the level, point it at an Actor that blocks the ECC_Visibility channel.
// Try moving in front of the trace with the player character, is the trace detecting it?
// To be seen the component needs to block the trace channel that you're using.
// In the character blueprint set the "Visibility" "Trace Response" to "Block" and try again.

// Goal: Get more information about the trace hit from the FHitResult.
// Continue with the Actor from the previous exercise.
// The FHitResult variable that you pass into LineTraceSingleByChannel contains information about the trace.
// Get the Actor that was hit from FHitResult and log its name.
// Draw a debug sphere at the ImpactPoint of the hit.
// Walk in and out of the trace and observe the changes.
// Add more Actors in front of the trace, movement Actors from Module 2 works great here.

class UTextRenderComponent;
class UArrowComponent;
UCLASS()
class GAMEDEVULTIMATE_API AFirstTraceActor : public AActor
{
	GENERATED_BODY()

public:
	AFirstTraceActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FirstTraceActor, meta = (AllowPrivateAccess = true))
	float TraceDistance{ 1000.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FirstTraceActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;
};
