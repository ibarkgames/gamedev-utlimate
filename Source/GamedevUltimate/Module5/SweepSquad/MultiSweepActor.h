// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MultiSweepActor.generated.h"

// Goal: Create an Actor that uses SweepMultiByChannel instead of the Single version.
// Just like the multi line trace, this version collects multiple FHitResults along the path.
// Log the name of every hit Actor to the screen.
// Place a mix of blocking and overlapping objects in front of the Actor and observe what gets collected.

class UTextRenderComponent;
UCLASS()
class GAMEDEVULTIMATE_API AMultiSweepActor : public AActor
{
	GENERATED_BODY()

public:
	AMultiSweepActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = MultiSweepActor, meta = (AllowPrivateAccess = true))
	float SweepLength{ 1000.f };

	UPROPERTY(EditAnywhere, Category = MultiSweepActor, meta = (AllowPrivateAccess = true))
	float SweepRadius{ 50.f };

	UPROPERTY(EditDefaultsOnly, Category = MultiSweepActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;

	UPROPERTY(VisibleAnywhere, Category = MultiSweepActor, meta = (AllowPrivateAccess = true))
	FTimerHandle TextTimer;

	UPROPERTY(EditAnywhere, Category = MultiSweepActor, meta = (AllowPrivateAccess = true))
	float TextDuration{ 3.f };
};
