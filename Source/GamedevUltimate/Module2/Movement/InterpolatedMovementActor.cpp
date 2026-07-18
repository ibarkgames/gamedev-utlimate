// Copyright iBarkGames


#include "InterpolatedMovementActor.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


AInterpolatedMovementActor::AInterpolatedMovementActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void AInterpolatedMovementActor::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	EndLocation += GetActorLocation();
}

void AInterpolatedMovementActor::Tick(const float DeltaTime)
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

