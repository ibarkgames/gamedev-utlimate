// Copyright iBarkGames


#include "ActorNamesOverlapActor.h"

#include "GamedevUltimate.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"


AActorNamesOverlapActor::AActorNamesOverlapActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void AActorNamesOverlapActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (bDebug)
		GetWorldTimerManager().SetTimer(
				TimerHandle,
				[this]() { LogOverlappingActors(); },
				1.f,
				true
			);
}

void AActorNamesOverlapActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActorNamesOverlapActor::LogOverlappingActors() const
{
	TArray<AActor*> OverlappingActors;
	BoxComponent->GetOverlappingActors(OverlappingActors);
	for (const AActor* Actor : OverlappingActors)
	{
		UE_LOG(LogGamedevUltimate, Log, TEXT("Overlapping Actor: %s"), *Actor->GetName())
	}
}

