// Copyright iBarkGames


#include "ContinuousRotationActor.h"

#include "Components/StaticMeshComponent.h"


AContinuousRotationActor::AContinuousRotationActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void AContinuousRotationActor::BeginPlay()
{
	Super::BeginPlay();
}

void AContinuousRotationActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(NewRotation);
}

