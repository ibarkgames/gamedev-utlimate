// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPadActor.generated.h"

class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API ALaunchPadActor : public AActor
{
	GENERATED_BODY()

public:
	ALaunchPadActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	UPROPERTY(EditDefaultsOnly, Blueprintable, Category=LaunchPadActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditDefaultsOnly, Blueprintable, Category=LaunchPadActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(EditAnywhere, Blueprintable, Category=LaunchPadActor, meta=(AllowPrivateAccess=true))
	float LaunchVelocityMagnitude{1000.f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=KillZoneActo, meta=(AllowPrivateAccess=true))
	bool bDebug{false};
};
