// Copyright iBarkGames


#include "SineWaveScaleActor.h"

#include "PrimitiveSceneProxy.h"
#include "Components/StaticMeshComponent.h"


ASineWaveScaleActor::ASineWaveScaleActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ASineWaveScaleActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASineWaveScaleActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Time += DeltaTime;
	const float Alpha = (FMath::Sin(Time) + 1.f) * 0.5f;
	const FVector NewScale = FMath::Lerp(MinScale, MaxScale, Alpha);
	SetActorScale3D(NewScale);
}

