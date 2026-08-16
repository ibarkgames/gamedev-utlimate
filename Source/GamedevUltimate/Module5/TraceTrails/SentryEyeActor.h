// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SentryEyeActor.generated.h"

// Goal: Create a Sentry Eye Actor that always knows if it can see the player.
// Trace from the sentry towards the player's location and figure out if the path is clear or blocked.
// Show the result visually: one color when the player is visible, another when the player is hiding.
// How you handle the details is up to you, test it by hiding behind walls.

class USphereComponent;
class UTextRenderComponent;

UCLASS()
class GAMEDEVULTIMATE_API ASentryEyeActor : public AActor
{
	GENERATED_BODY()

public:
	ASentryEyeActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SentEyeActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SentEyeActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SentEyeActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = TraceRadarActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TraceRadarActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<ACharacter> TraceRadarCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SentEyeActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SentEyeActor, meta = (AllowPrivateAccess = true))
	float RotationSpeed{ 50.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SentEyeActor, meta = (AllowPrivateAccess = true))
	float TraceDistance{ 250.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SentEyeActor, meta = (AllowPrivateAccess = true))
	FTimerHandle WarningTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SentEyeActor, meta = (AllowPrivateAccess = true))
	float WarningMessageTime{ 3.f };
};
