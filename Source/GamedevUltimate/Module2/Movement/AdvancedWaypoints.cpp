// Copyright iBarkGames


#include "AdvancedWaypoints.h"

#include "Components/StaticMeshComponent.h"


AAdvancedWaypoints::AAdvancedWaypoints()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void AAdvancedWaypoints::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAdvancedWaypoints::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (WayPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No WayPoints were found"));
		return;
	}
	if (WayPoints.Num() == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough WayPoints were set"));
		return;
	}
	
	FVector NewLocation = GetActorLocation();
	const FVector EndLocation = WayPoints[NextWaypointIndex]->GetActorLocation();
	if (NewLocation.Equals(EndLocation))
	{
		if (!bIsReturning && NextWaypointIndex == WayPoints.Num() - 1)
		{
			bIsReturning = true;
			NextWaypointIndex--;
		}
		else if (!bIsReturning)
		{
			NextWaypointIndex++;
		}
		else if (bIsReturning && NextWaypointIndex == 0)
		{
			bIsReturning = false;
			NextWaypointIndex++;
		}
		else if (bIsReturning)
		{
			NextWaypointIndex--;
		}
	}
	
	NewLocation = FMath::VInterpConstantTo(NewLocation, EndLocation, DeltaTime, Speed);
	SetActorLocation(NewLocation);
}

