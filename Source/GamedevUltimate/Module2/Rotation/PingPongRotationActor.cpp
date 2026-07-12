// Copyright iBarkGames


#include "PingPongRotationActor.h"

#include "Components/StaticMeshComponent.h"


APingPongRotationActor::APingPongRotationActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void APingPongRotationActor::BeginPlay()
{
	Super::BeginPlay();
}

void APingPongRotationActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FRotator NewRotation = GetActorRotation();
	if (bIsReturning)
	{
		NewRotation.Yaw -= DeltaTime * YawRotationSpeed;
		if (NewRotation.Yaw <= 0.f) bIsReturning = false;
	}
	else
	{
		NewRotation.Yaw += DeltaTime * YawRotationSpeed;
		if (NewRotation.Yaw >= MaxYawRotation) bIsReturning = true;
	}
	SetActorRotation(NewRotation);
}

