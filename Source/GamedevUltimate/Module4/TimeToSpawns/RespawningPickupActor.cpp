// Copyright iBarkGames

#include "RespawningPickupActor.h"

ARespawningPickupActor::ARespawningPickupActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneComponent);
}

void ARespawningPickupActor::BeginPlay()
{
	Super::BeginPlay();
	ScheduleSpawning();
}

void ARespawningPickupActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ARespawningPickupActor::ScheduleSpawning()
{
	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		[this] {
			const FVector Location =  GetActorLocation() + SpawnRelativeLocation;
			const FRotator Rotation = GetActorRotation();
			AActor* SpawnedActor = GetWorld()->SpawnActor(ActorClassToSpawn, &Location, &Rotation);
			if (SpawnedActor)
			{
				SpawnedActor->OnDestroyed.AddDynamic(this, &ARespawningPickupActor::HandleSpawnedActorDestroyed);
			}
		},
		SpawnDelay,
		false
	);
}

void ARespawningPickupActor::HandleSpawnedActorDestroyed(AActor* DestroyedActor)
{
	ScheduleSpawning();
}
