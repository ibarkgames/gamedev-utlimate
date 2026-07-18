// Copyright iBarkGames


#include "UniformScaleActor.h"

#include "Components/StaticMeshComponent.h"


AUniformScaleActor::AUniformScaleActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void AUniformScaleActor::BeginPlay()
{
	Super::BeginPlay();
}

void AUniformScaleActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NextScale = GetActorScale3D();
	if (NextScale.X >= MaxScale)
	{
		return;
	}
	
	NextScale += FVector{1.0f, 1.0f, 1.0f} * DeltaTime * ScaleSpeed;
	SetActorScale3D(NextScale);
}

