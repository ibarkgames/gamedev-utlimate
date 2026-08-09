// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StockKeeperActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API AStockKeeperActor : public AActor
{
	GENERATED_BODY()

public:
	AStockKeeperActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void Spawn(int Index);
	
	UFUNCTION()
	void HandleSpawnedActorDestroyed(AActor* DestroyedActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StockKeeperActor, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StockKeeperActor, meta = (AllowPrivateAccess = "true"))
	TArray<FTimerHandle> TimerHandles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StockKeeperActor, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorClassToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StockKeeperActor, meta = (AllowPrivateAccess = "true"))
	float SpawnRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StockKeeperActor, meta = (AllowPrivateAccess = "true"))
	FVector SpawnInitialOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StockKeeperActor, meta = (AllowPrivateAccess = "true"))
	FVector SpawnOffsetBetween;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StockKeeperActor, meta = (AllowPrivateAccess = "true"))
	int32 MaxSpawns;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StockKeeperActor, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AActor>> SpawnedActors;
};
