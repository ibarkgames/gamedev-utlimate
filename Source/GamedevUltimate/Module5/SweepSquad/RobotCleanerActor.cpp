// Copyright iBarkGames

#include "RobotCleanerActor.h"

#include "Components/ArrowComponent.h"

ARobotCleanerActor::ARobotCleanerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(RootComponent);
}

void ARobotCleanerActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARobotCleanerActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const FVector DeltaLocation = FVector::ForwardVector * DeltaTime * Speed;
	AddActorLocalOffset(DeltaLocation, bSweep, &HitResult);

	if (HitResult.bBlockingHit)
	{
		const int32 RandomInt = FMath::RandRange(1, 3);
		FRotator Rotator = GetActorRotation();

		Rotator.Yaw += 90 * RandomInt;
		if (Rotator.Yaw >= 360.f)
		{
			Rotator.Yaw -= 360.f;
		}
		SetActorRotation(Rotator);
	}
}
