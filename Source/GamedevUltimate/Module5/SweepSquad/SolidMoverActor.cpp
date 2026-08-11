// Copyright iBarkGames

#include "SolidMoverActor.h"

#include "Components/ArrowComponent.h"

ASolidMoverActor::ASolidMoverActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(RootComponent);
}

void ASolidMoverActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASolidMoverActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const FVector DeltaLocation = FVector::ForwardVector * DeltaTime * Speed;
	AddActorLocalOffset(DeltaLocation, bSweep, &HitResult);

	if (HitResult.bBlockingHit)
	{
		FRotator Rotator = GetActorRotation();
		Rotator.Yaw += 180;
		if (Rotator.Yaw >= 360.f)
		{
			Rotator.Yaw -= 360.f;
		}
		SetActorRotation(Rotator);
	}
}
