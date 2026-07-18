// Copyright iBarkGames


#include "OrbitRotationActor.h"

#include "Components/StaticMeshComponent.h"


AOrbitRotationActor::AOrbitRotationActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetRelativeLocation(FVector(RotationRadius, 0.0f, 0.0f));
}

void AOrbitRotationActor::BeginPlay()
{
	Super::BeginPlay();
}

void AOrbitRotationActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(NewRotation);
}

