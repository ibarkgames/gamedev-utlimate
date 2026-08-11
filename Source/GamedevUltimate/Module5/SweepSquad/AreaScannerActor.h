// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AreaScannerActor.generated.h"

// Goal: Scan an area for Actors by doing an overlap test.
// Sometimes you don't want to move a shape, you just want to ask: "what is inside this area right now?".
// Create an Actor that checks a sphere area around itself using the OverlapMultiByChannel function.
// This function uses a TArray of FOverlapResults instead of hit results.
// Log the name of every Actor found inside the area.
// Draw a debug sphere so you can see the scanned area.
// Try to answer this question: How is this different from the GetOverlappingActors function from Module 3? Notice that
// this Actor doesn't need any collision component at all.

class UTextRenderComponent;
UCLASS()
class GAMEDEVULTIMATE_API AAreaScannerActor : public AActor
{
	GENERATED_BODY()

public:
	AAreaScannerActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = MultiSweepActor, meta = (AllowPrivateAccess = true))
	float SweepRadius{ 500.f };

	UPROPERTY(EditAnywhere, Category = MultiSweepActor, meta = (AllowPrivateAccess = true))
	float DebugSphereRadius{ 50.f };

	UPROPERTY(EditDefaultsOnly, Category = MultiSweepActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;

	UPROPERTY(VisibleAnywhere, Category = MultiSweepActor, meta = (AllowPrivateAccess = true))
	FTimerHandle TextTimer;

	UPROPERTY(EditAnywhere, Category = MultiSweepActor, meta = (AllowPrivateAccess = true))
	float TextDuration{ 3.f };
};
