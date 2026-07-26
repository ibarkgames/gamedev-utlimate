// Copyright iBarkGames


#include "OverlapCounterActor.h"

#include "GamedevUltimate.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"


AOverlapCounterActor::AOverlapCounterActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void AOverlapCounterActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AOverlapCounterActor::OnComponentBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AOverlapCounterActor::OnComponentEndOverlap);
}

void AOverlapCounterActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bInitialized)
	{
		TArray<AActor*> OverlappedActors;
		OverlappedActors.Empty();
		BoxComponent->GetOverlappingActors(OverlappedActors);
		OverlapCounter = OverlappedActors.Num();
		if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("Overlapped actors: %i"), OverlapCounter);
		bInitialized = true;
	}
}

void AOverlapCounterActor::OnComponentBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (OtherActor && OtherActor != this)
	{
		OverlapCounter++;
		if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("Overlapped actors: %i"), OverlapCounter);
	}
}

void AOverlapCounterActor::OnComponentEndOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex
)
{
	if (OtherActor && OtherActor != this)
	{
		OverlapCounter--;
		if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("Overlapped actors: %i"), OverlapCounter);
	}
}

