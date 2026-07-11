// Copyright iBarkGames


#include "SplineBasedMovementActor.h"

#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


ASplineBasedMovementActor::ASplineBasedMovementActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ASplineBasedMovementActor::BeginPlay()
{
	Super::BeginPlay();

	if (SplineActor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("SplineBasedMovementActor::BeginPlay() No SplineComponent set"));
		return;
	}

	SplineComponent = SplineActor->FindComponentByClass<USplineComponent>();
	SplineLength = SplineComponent->GetSplineLength();
}

void ASplineBasedMovementActor::Tick(const float DeltaTime)
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
	const FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(
		Distance, ESplineCoordinateSpace::World);
	SetActorLocation(NewLocation);
}
