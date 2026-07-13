// Copyright iBarkGames


#include "RandomizeScaleActor.h"

#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"


ARandomizeScaleActor::ARandomizeScaleActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ARandomizeScaleActor::BeginPlay()
{
	Super::BeginPlay();
	SetTargetScales();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARandomizeScaleActor::SetTargetScales, 1.0f, true);
}

void ARandomizeScaleActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewScale = GetActorScale3D();
	NewScale.X += DeltaTime * ScalingSpeed;
	NewScale.Y += DeltaTime * ScalingSpeed;
	NewScale.Z += DeltaTime * ScalingSpeed;
	
	NewScale.X = FMath::Clamp(NewScale.X, MinScales.X, TargetScales.X);
	NewScale.Y = FMath::Clamp(NewScale.Y, MinScales.Y, TargetScales.Y);
	NewScale.Z = FMath::Clamp(NewScale.Z, MinScales.Z, TargetScales.Z);
	
	SetActorScale3D(NewScale);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
}

void ARandomizeScaleActor::SetTargetScales()
{
	TargetScales = FVector(
		FMath::RandRange(MinScales.X, MaxScales.X),
		FMath::RandRange(MinScales.Y, MaxScales.Y),
		FMath::RandRange(MinScales.Z, MaxScales.Z)
	);
}

