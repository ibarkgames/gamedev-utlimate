// Copyright iBarkGames


#include "TimeMeasuringOverlapActor.h"

#include "GamedevUltimate.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"


ATimeMeasuringOverlapActor::ATimeMeasuringOverlapActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionBox->SetupAttachment(RootComponent);
	
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
}

void ATimeMeasuringOverlapActor::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATimeMeasuringOverlapActor::OnComponentBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ATimeMeasuringOverlapActor::OnComponentEndOverlap);
	
	OverlappingActorTimes.Empty();
	TArray<AActor*> OverlappingActors;
	CollisionBox->GetOverlappingActors(OverlappingActors);
	for (const AActor* OverlappingActor : OverlappingActors)
	{
		if (IsValid(OverlappingActor))
		{
			OverlappingActorTimes.Add(OverlappingActor->GetName(), 0.f);
		}
	}
}

void ATimeMeasuringOverlapActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	for (TTuple<FString, float> OverlappingActor : OverlappingActorTimes)
	{
		OverlappingActorTimes[OverlappingActor.Key] = OverlappingActor.Value + DeltaTime;
	}
}

void ATimeMeasuringOverlapActor::OnComponentBeginOverlap(
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
		OverlappingActorTimes.Add(OtherActor->GetName(), 0.f);
	}
}

void ATimeMeasuringOverlapActor::OnComponentEndOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex
)
{
	if (OtherActor && OtherActor != this)
	{
		if (OverlappingActorTimes.Contains(OtherActor->GetName()))
		{
			if (bDebug)
				UE_LOG(
					LogGamedevUltimate,
					Log, 
					TEXT("%s stayed for %f seconds."), *OtherActor->GetName(), OverlappingActorTimes[OtherActor->GetName()]
				);
			
			OverlappingActorTimes.Remove(OtherActor->GetName());
		}
	}
}

