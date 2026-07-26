// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeferredSpawningActor.generated.h"

class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API ADeferredSpawningActor : public AActor
{
	GENERATED_BODY()

	/*
*Goal: Learn how to use the deferred spawning functionality.
You can use the SpawnActorDeferred function to defer the spawn time of an Actor.
Create an Actor that deffered spawns another Actor in BeginPlay.
Finish the spawning using an overlap or hit event.
Try to think of scenarios where deferred spawning might be useful.
	 */
	
public:
	ADeferredSpawningActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DeferredSpawningActor, meta =(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DeferredSpawningActor, meta =(AllowPrivateAccess=true))
	TSubclassOf<AActor> ActorClassToSpawn;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=DeferredSpawningActor, meta =(AllowPrivateAccess=true))
	TObjectPtr<AActor> SpawnedActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DeferredSpawningActor, meta =(AllowPrivateAccess=true))
	bool bDebug{false};
};
