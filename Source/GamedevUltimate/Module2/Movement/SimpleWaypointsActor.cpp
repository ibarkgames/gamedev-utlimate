// Copyright iBarkGames


#include "SimpleWaypointsActor.h"

#include "Components/StaticMeshComponent.h"


ASimpleWaypointsActor::ASimpleWaypointsActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ASimpleWaypointsActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (StartActor != nullptr && EndActor != nullptr)
	{
		StartLocation = StartActor->GetActorLocation();
		EndLocation = EndActor->GetActorLocation();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StartActor or/and EndActor is nullptr"));
		StartLocation = GetActorLocation();
		EndLocation = GetActorLocation();
	}
}

void ASimpleWaypointsActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation();
	if (bIsReturning)
	{
		NewLocation = FMath::VInterpConstantTo(NewLocation, StartLocation, DeltaTime, Speed);
		if (NewLocation == StartLocation)
		{
			bIsReturning = false;
		} 
	}
	else
	{
		NewLocation = FMath::VInterpConstantTo(NewLocation, EndLocation, DeltaTime, Speed);
		if (NewLocation == EndLocation)
		{
			bIsReturning = true;
		}
	}
	SetActorLocation(NewLocation);
}

