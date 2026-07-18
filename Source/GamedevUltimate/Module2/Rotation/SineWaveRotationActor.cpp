// Copyright iBarkGames


#include "SineWaveRotationActor.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


// Sets default values
ASineWaveRotationActor::ASineWaveRotationActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ASineWaveRotationActor::BeginPlay()
{
	Super::BeginPlay();
	
	Start = GetActorRotation();
}

void ASineWaveRotationActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Time += DeltaTime;
	const float Alpha = (FMath::Sin(Time) + 1.f) / 2.f;
	const FRotator NewRotation = FMath::Lerp(Start, End, Alpha);
	SetActorRotation(NewRotation);
}

