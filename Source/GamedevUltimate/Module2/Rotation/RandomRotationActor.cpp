// Copyright iBarkGames


#include "RandomRotationActor.h"

#include "Components/StaticMeshComponent.h"


ARandomRotationActor::ARandomRotationActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ARandomRotationActor::BeginPlay()
{
	Super::BeginPlay();

	switch (FMath::RandRange(0, 2))
	{
	case 0: bIsYawRotationEnabled = true; break;
	case 1: bIsPitchRotationEnabled = true; break;
	case 2: bIsRollRotationEnabled = true; break;
	default: ;
	}
}

void ARandomRotationActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	// FRotator NewRotation = GetActorRotation();
	// if (bIsYawRotationEnabled) NewRotation.Yaw += YawRotationSpeed * DeltaTime;
	// if (bIsPitchRotationEnabled) NewRotation.Pitch += PitchRotationSpeed * DeltaTime;
	// if (bIsRollRotationEnabled) NewRotation.Roll += RollRotationSpeed * DeltaTime;
	// SetActorRotation(NewRotation);
	
	if (bIsYawRotationEnabled) AccumulatedYaw += YawRotationSpeed * DeltaTime;
	if (bIsPitchRotationEnabled) AccumulatedPitch += PitchRotationSpeed * DeltaTime;
	if (bIsRollRotationEnabled) AccumulatedRoll += RollRotationSpeed * DeltaTime;

	SetActorRotation(FRotator(AccumulatedPitch, AccumulatedYaw, AccumulatedRoll));
}
