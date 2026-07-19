// Copyright iBarkGames


#include "LayeredZoneOverlapActor.h"

#include "GamedevUltimate.h"
#include "Components/SphereComponent.h"


ALayeredZoneOverlapActor::ALayeredZoneOverlapActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	InnerSphere = CreateDefaultSubobject<USphereComponent>("InnerSphere");
	InnerSphere->SetupAttachment(RootComponent);
	
	OuterSphere = CreateDefaultSubobject<USphereComponent>("OuterSphere");
	OuterSphere->SetupAttachment(RootComponent);
}

void ALayeredZoneOverlapActor::BeginPlay()
{
	Super::BeginPlay();
	
	InnerSphere->OnComponentBeginOverlap.AddDynamic(this, &ALayeredZoneOverlapActor::OnComponentBeginOverlap);
	OuterSphere->OnComponentBeginOverlap.AddDynamic(this, &ALayeredZoneOverlapActor::OnComponentBeginOverlap);
}

void ALayeredZoneOverlapActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALayeredZoneOverlapActor::OnComponentBeginOverlap(
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
		if (OverlappedComponent == InnerSphere)
		{
			if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("You are right next to me!"));
		} else if (OverlappedComponent == OuterSphere)
		{
			if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("You are getting close!"));
		}
	}
}
