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
	const float Alpha = FMath::Sin(Time);
	const FRotator NewRotation = FMath::Lerp(Start, End, Alpha);
	SetActorRotation(NewRotation);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(21, 2.0f, FColor::Green,
										 FString::Printf(TEXT("Actor Rotation: %s, Time: %f, Sin: %f, Alpha: %f"), 
											 *NewRotation.ToString(), Time, FMath::Sin(Time), Alpha)
											 );
	}
}

