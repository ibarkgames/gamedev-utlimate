// Copyright iBarkGames


#include "DirectionalMovement.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


ADirectionalMovement::ADirectionalMovement()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	MovingDirection = CreateDefaultSubobject<UArrowComponent>(FName("Direction"));
	MovingDirection->SetupAttachment(RootComponent);
}

void ADirectionalMovement::BeginPlay()
{
	Super::BeginPlay();
}

void ADirectionalMovement::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation();
	const FVector Direction = MovingDirection->GetComponentRotation().Vector().GetSafeNormal();
	NewLocation += Direction * MovingSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

 