// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TraceRadarActor.generated.h"

// Goal: Implement a Rotating Radar that can detect the Player.
// Create an Actor that continuously rotates and line traces forwards, like a lighthouse beam.
// You know how to rotate Actors, combine it with a line trace.
// When the beam detects the player, log a message: "Intruder detected!".
// Only the Player should be able to trigger the radar.
// Bonus: Change the material color of the Actor while the player is detected by the radar.

class USphereComponent;
class UTextRenderComponent;
UCLASS()
class GAMEDEVULTIMATE_API ATraceRadarActor : public AActor
{
	GENERATED_BODY()

public:
	ATraceRadarActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = TraceRadarActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = TraceRadarActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TraceRadarActor, meta = (AllowPrivateAccess = true))
	float RotatingSpeed{ 50.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TraceRadarActor, meta = (AllowPrivateAccess = true))
	float TraceDistance{ 250.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TraceRadarActor, meta = (AllowPrivateAccess = true))
	FTimerHandle WarningTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TraceRadarActor, meta = (AllowPrivateAccess = true))
	float WarningMessageTime{ 3.f };
};
