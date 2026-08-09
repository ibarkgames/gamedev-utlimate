// Copyright iBarkGames

#include "StockKeeperActor.h"

#include "GamedevUltimate.h"

// Goal: Create a spawner that keeps exactly 5 coins available inside an area at all times.
// Same logic as "Respawning Pickup" now applied to multiple pickups simultaneously.
// Hint: Actors fire an event when they are destroyed.

AStockKeeperActor::AStockKeeperActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void AStockKeeperActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnedActors.SetNum(MaxSpawns);
	TimerHandles.SetNum(MaxSpawns);
	
	for (int i = 0; i < MaxSpawns; i++)
	{
		Spawn(i);
	}
}

void AStockKeeperActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AStockKeeperActor::Spawn(int Index)
{
	GetWorldTimerManager().SetTimer(
		TimerHandles[Index],
		[this, Index] {
			const FVector SpawnLocation = GetActorLocation() + SpawnInitialOffset + SpawnOffsetBetween * Index;
			const FRotator Rotation = GetActorRotation();
			AActor* Actor = GetWorld()->SpawnActor(ActorClassToSpawn, &SpawnLocation, &Rotation);
			if (Actor)
			{
				Actor->OnDestroyed.AddDynamic(this, &AStockKeeperActor::HandleSpawnedActorDestroyed);
				SpawnedActors[Index] = Actor;
			}
		}, 
		SpawnRate,
		false
	);
}

void AStockKeeperActor::HandleSpawnedActorDestroyed(AActor* DestroyedActor)
{
	for (int i = 0; i < MaxSpawns; i++)
	{
		if (SpawnedActors[i] == DestroyedActor)
		{
			Spawn(i);
		}
	}
}
