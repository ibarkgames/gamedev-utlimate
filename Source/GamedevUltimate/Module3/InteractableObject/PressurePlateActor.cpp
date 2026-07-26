// Copyright iBarkGames


#include "PressurePlateActor.h"

#include "GamedevUltimate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


APressurePlateActor::APressurePlateActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(Mesh);
}

void APressurePlateActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APressurePlateActor::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APressurePlateActor::OnEndOverlap);
	
	StartLocation = GetActorLocation().Z;
	EndLocation = GetActorLocation().Z - TravelingDistance;
}

void APressurePlateActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NextLocation = GetActorLocation();
	float DeltaZ = 0.f;
	if (Actors.Num() == 0 && NextLocation.Z < StartLocation)
	{
		DeltaZ += DeltaTime * TravelingSpeed;
	}
	else if (Actors.Num() != 0 && NextLocation.Z > EndLocation)
	{
		DeltaZ -= DeltaTime * TravelingSpeed;
	}
	
	if (DeltaZ != 0.f)
	{
		NextLocation.Z += DeltaZ;
		SetActorLocation(NextLocation);
	}
}

void APressurePlateActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (OtherActor && OtherActor != this && !Actors.Contains(OtherActor))
	{
		if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("OnBeginOverlap OtherActor: %p"), OtherActor);
		Actors.AddUnique(OtherActor);
	}
}

void APressurePlateActor::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex
)
{
	if (OtherActor && OtherActor != this && Actors.Contains(OtherActor))
	{
		if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("OnEndOverlap OtherActor: %p"), OtherActor);
		Actors.Remove(OtherActor);
	}
}
