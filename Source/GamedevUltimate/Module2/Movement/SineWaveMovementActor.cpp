// Copyright iBarkGames


#include "SineWaveMovementActor.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


ASineWaveMovementActor::ASineWaveMovementActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ASineWaveMovementActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASineWaveMovementActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Time += DeltaTime;
	const float Alpha = (FMath::Sin(Time) + 1.f) * 0.5f;
	const FVector NewLocation = FMath::Lerp(Start, End, Alpha);
	SetActorLocation(NewLocation);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(21, 2.0f, FColor::Green,
										 FString::Printf(TEXT("Actor Location: %s, Time: %f, Sin: %f, Alpha: %f"), 
											 *NewLocation.ToString(), Time, FMath::Sin(Time), Alpha)
											 );
	}
}

