// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XRayTraceActor.generated.h"

// Goal: Learn how to do a trace that can detect multiple objects.
// Create an Actor that does a line trace using LineTraceMultiByChannel instead of the Single version.
// This version uses a TArray of FHitResults and can detect multiple objects along the trace.
// Log the name of every hit Actor to the screen.
// Place a mix of blocking and overlapping objects in front of the Actor.
// Try to answer this question: Does the multi trace go through blocking objects? Which objects does it collect along
// the way?

class UTextRenderComponent;
UCLASS()
class GAMEDEVULTIMATE_API AXRayTraceActor : public AActor
{
	GENERATED_BODY()

public:
	AXRayTraceActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = XRayTraceActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = XRayTraceActor, meta = (AllowPrivateAccess = true))
	float TraceDistance{ 1000.f };
};
