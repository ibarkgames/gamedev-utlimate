// Copyright iBarkGames


#include "DistanceBasedScaleActor.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


ADistanceBasedScaleActor::ADistanceBasedScaleActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ADistanceBasedScaleActor::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	StartScale = GetActorScale3D();
}

void ADistanceBasedScaleActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation();
	FVector MovementDirection = EndLocation - StartLocation;
	MovementDirection.Normalize();
	
	if (bIsReturning)
	{
		NewLocation -= MovementDirection * DeltaTime * MovingSpeed;
		if ((EndLocation - NewLocation).Length() >= (EndLocation - StartLocation).Length())
		{
			bIsReturning = false;
		}
	}
	else
	{
		NewLocation += MovementDirection * DeltaTime * MovingSpeed;
		if ((NewLocation - StartLocation).Length() >= (EndLocation - StartLocation).Length())
		{
			bIsReturning = true;
		}
	}

	const float Distance = (NewLocation - StartLocation).Length();
	const float MaxDistance = (EndLocation - StartLocation).Length();
	if (MaxDistance > 0.f)
	{
		const FVector NewScale = StartScale * Distance / MaxDistance;
		SetActorScale3D(NewScale);
	}
	
	SetActorLocation(NewLocation);
}

