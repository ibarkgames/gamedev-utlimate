// Copyright iBarkGames

#include "FirstDelayActor.h"

AFirstDelayActor::AFirstDelayActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void AFirstDelayActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		[this]() {
			FRotator NewRotation = GetActorRotation();
			NewRotation.Yaw += FMath::RandRange(MinRotation, MaxRotation);
			SetActorRotation(NewRotation);
		},
		LoopTime,
		true,
		FirstDelay
	);
}

void AFirstDelayActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

