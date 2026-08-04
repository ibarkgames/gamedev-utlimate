// Copyright iBarkGames

#include "BomberBlimpActor.h"

#include "CannonProjectileActor.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"

ABomberBlimpActor::ABomberBlimpActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void ABomberBlimpActor::BeginPlay()
{
	Super::BeginPlay();

	if (SplineActor == nullptr)
	{
		return;
	}

	SplineComponent = SplineActor->FindComponentByClass<USplineComponent>();
	if (SplineComponent == nullptr)
	{
		return;
	}
	SplineLength = SplineComponent->GetSplineLength();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABomberBlimpActor::OnBeginOverlap);

	Schedule();
}

void ABomberBlimpActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SplineComponent == nullptr)
	{
		return;
	}

	Distance += DeltaTime * Speed;
	if (Distance > SplineLength)
	{
		Distance -= SplineLength;
	}
	const FVector NewLocation =
		SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	SetActorLocation(NewLocation);
	if (IsValid(SpawnedActor) && !SpawnedActor->IsPhysicsEnabled())
	{
		SpawnedActor->SetActorLocation(NewLocation + SpawnOffset);
	}
}

void ABomberBlimpActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(SpawnedActor)) return;
	
	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		SpawnedActor->SetSimulatePhysics(true);
		SpawnedActor->SetLifeSpan(SpawnedActorLifeSpawn);
	}
}

void ABomberBlimpActor::Schedule()
{
	if (!IsValid(SpawnedActor) && !bIsSpawnScheduled)
	{
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			[this] {
				bIsSpawnScheduled = true;
				const FVector SpawnLocation = GetActorLocation() + SpawnOffset;
				const FRotator SpawnRotation = GetActorRotation();
				FActorSpawnParameters Params = FActorSpawnParameters();
				Params.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				if (AActor* Actor = GetWorld()->SpawnActor(SpawnedActorClass, &SpawnLocation, &SpawnRotation, Params);
					Actor != nullptr)
				{
					if (ACannonProjectileActor* Projectile = Cast<ACannonProjectileActor>(Actor); Projectile != nullptr)
					{
						SpawnedActor = Projectile;
						Projectile->OnDestroyed.AddDynamic(this, &ABomberBlimpActor::HandleSpawnedActorDestroyed);
						Projectile->SetSimulatePhysics(false);
					}
				}
			},
			SpawnDelay, false);
	}
}

void ABomberBlimpActor::HandleSpawnedActorDestroyed(AActor* DestroyedActor)
{
	bIsSpawnScheduled = false;
	SpawnedActor = nullptr;
	Schedule();
}
