// Copyright iBarkGames

#include "CannonActor.h"

#include "CannonProjectileActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

class ACannonProjectileActor;
ACannonActor::ACannonActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void ACannonActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACannonActor::OnBeginOverlap);
}

void ACannonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ACannonActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACharacter::StaticClass()) && !bScheduled)
	{
		bScheduled = true;
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			[this] {
				const FVector		  Location = GetActorLocation() + GetActorForwardVector() * SpawnOffset;
				const FRotator		  Rotation = GetActorRotation();
				FActorSpawnParameters Parameters = FActorSpawnParameters();
				Parameters.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				Parameters.Owner = this;
				if (AActor* Actor = GetWorld()->SpawnActor(ProjectileClass, &Location, &Rotation, Parameters))
				{
					Shoot(Actor);
				}
			},
			Delay, false);
	}
}

void ACannonActor::Shoot(AActor* Actor)
{
	Actor->SetLifeSpan(SpawnedActorLifeSpawn);

	if (ACannonProjectileActor* Projectile = Cast<ACannonProjectileActor>(Actor))
	{
		FRotator LaunchRotation = GetActorRotation();
		LaunchRotation.Pitch += ElevationAngle;
		const FVector LaunchVelocity = LaunchRotation.Vector() * StartVelocity;
		Projectile->Launch(LaunchVelocity);
	}
	bScheduled = false;
}
