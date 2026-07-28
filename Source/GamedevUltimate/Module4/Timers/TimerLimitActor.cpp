// Copyright iBarkGames

#include "TimerLimitActor.h"

#include "GamedevUltimate.h"

ATimerLimitActor::ATimerLimitActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneComponent);
}

void ATimerLimitActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		[this] {
			FVector NewLocation = GetActorLocation();
			NewLocation.Z += FMath::RandRange(MinElevation, MaxElevation);
			SetActorLocation(NewLocation);
			LoopCounter++;
			if (LoopCounter >= LoopCounterLimit)
			{
				if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("ATimerLimitActor: Stop timer"));
				GetWorldTimerManager().ClearTimer(TimerHandle);
			}
		},
		LoopTime,
		true
	);
}

void ATimerLimitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

