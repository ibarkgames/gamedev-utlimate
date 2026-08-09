// Copyright iBarkGames

#include "IcicleTrapActor.h"

#include "IcicleSpikeActor.h"
#include "Components/BoxComponent.h"

AIcicleTrapActor::AIcicleTrapActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void AIcicleTrapActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AIcicleTrapActor::OnBeginOverlap);
	
	Schedule();
}

void AIcicleTrapActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIcicleTrapActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(SpawnedActor))
	{
		SpawnedActor->TurnPhysicsOn();
	}
}
void AIcicleTrapActor::Schedule()
{
	if (!IsValid(SpawnedActor) && !bIsSpawnScheduled)
	{
		bIsSpawnScheduled = true;
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			[this] {
				const FVector SpawnLocation = GetActorLocation() + SpawnOffset;
				const FRotator SpawnRotation = GetActorRotation() + SpawnRotatorOffset;
				FActorSpawnParameters Params;
				Params.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				if (AActor*Actor =
						GetWorld()->SpawnActor(IcicleSpikeClass, &SpawnLocation, &SpawnRotation, Params);
					Actor != nullptr)
				{
					if (AIcicleSpikeActor* SpikeActor = Cast<AIcicleSpikeActor>(Actor); SpikeActor != nullptr)
					{
						SpawnedActor = SpikeActor;
						SpawnedActor->OnDestroyed.AddDynamic(this, &AIcicleTrapActor::HandleSpawnedActorDestroyed);
						return;
					}

					Actor->Destroy();
				}

				bIsSpawnScheduled = false;
				Schedule();
			},
			SpawnDelay, false);
	}
}
void AIcicleTrapActor::HandleSpawnedActorDestroyed(AActor* DestroyedActor)
{
	bIsSpawnScheduled = false;
	SpawnedActor = nullptr;
	Schedule();
}
