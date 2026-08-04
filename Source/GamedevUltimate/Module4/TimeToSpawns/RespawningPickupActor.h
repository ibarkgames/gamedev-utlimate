// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RespawningPickupActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ARespawningPickupActor : public AActor
{
	GENERATED_BODY()

public:
	ARespawningPickupActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void ScheduleSpawning();
	
	UFUNCTION()
	void HandleSpawnedActorDestroyed(AActor* DestroyedActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RespawningPickupActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RespawningPickupActor, meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> ActorClassToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RespawningPickupActor, meta = (AllowPrivateAccess = true))
	FVector SpawnRelativeLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RespawningPickupActor, meta = (AllowPrivateAccess = true))
	FTimerHandle SpawnTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RespawningPickupActor, meta = (AllowPrivateAccess = true))
	float SpawnDelay;
};
