// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapActor.generated.h"

class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API ATrapActor : public AActor
{
	GENERATED_BODY()

	/*
*Goal: Create a Trap Actor that spawns something when the player walks into its trigger box.
You mastered overlap events and player filtering in Module 3, combine them with spawning.
Spawn something dramatic above the player's head, a physics cube falling from the sky works great.
Add the option to make the trap one-shot, if set to true it should only trigger once.
	 */
	
public:
	ATrapActor();

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TrapActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TrapActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TrapActor, meta=(AllowPrivateAccess=true))
	TSubclassOf<AActor> ActorToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TrapActor, meta=(AllowPrivateAccess=true))
	FVector SpawnOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=TrapActor, meta =(AllowPrivateAccess=true))
	bool bDebug{false};
};
