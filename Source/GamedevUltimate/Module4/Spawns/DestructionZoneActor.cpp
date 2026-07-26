// Copyright iBarkGames


#include "DestructionZoneActor.h"

#include "Components/BoxComponent.h"


ADestructionZoneActor::ADestructionZoneActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void ADestructionZoneActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestructionZoneActor::OnBeginOverlap);
}

void ADestructionZoneActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADestructionZoneActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

