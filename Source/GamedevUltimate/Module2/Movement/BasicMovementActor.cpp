// Copyright iBarkGames


#include "BasicMovementActor.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"


ABasicMovementActor::ABasicMovementActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ABasicMovementActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABasicMovementActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += MovingDirection.GetSafeNormal() * MovingSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}
