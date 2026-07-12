// Copyright iBarkGames


#include "MultiAxisRotationActor.h"

#include "Components/StaticMeshComponent.h"


AMultiAxisRotationActor::AMultiAxisRotationActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void AMultiAxisRotationActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMultiAxisRotationActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FQuat DeltaRotation = FQuat(FRotator(
		PitchRotationSpeed * DeltaTime,
		YawRotationSpeed * DeltaTime,
		RollRotationSpeed * DeltaTime
	));
	const FQuat NewRotation = GetActorQuat() * DeltaRotation;
	SetActorRotation(NewRotation);
}
