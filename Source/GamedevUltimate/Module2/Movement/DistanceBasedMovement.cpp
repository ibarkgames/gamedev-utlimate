// Copyright iBarkGames


#include "DistanceBasedMovement.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


ADistanceBasedMovement::ADistanceBasedMovement()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);

	MovingDirection = CreateDefaultSubobject<UArrowComponent>("Direction");
	MovingDirection->SetupAttachment(RootComponent);
}

void ADistanceBasedMovement::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

void ADistanceBasedMovement::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	const FVector Direction = MovingDirection->GetForwardVector().GetSafeNormal();
	NewLocation += Direction * MovingSpeed * DeltaTime;

	const float Distance = (NewLocation - StartLocation).Length();
	if ((!bIsReturning && Distance > MaxDistance) || (bIsReturning && Distance - DistanceThreshold < 0.f))
	{
		bIsReturning = !bIsReturning;
		FRotator RelativeRotation = MovingDirection->GetRelativeRotation();
		RelativeRotation.Yaw += 180.f;
		MovingDirection->SetRelativeRotation(RelativeRotation);
	} 
	SetActorLocation(NewLocation);
}
