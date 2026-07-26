// Copyright iBarkGames


#include "ActivatedPlatform.h"

#include "GamedevUltimateCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


AActivatedPlatform::AActivatedPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(Mesh);
}

void AActivatedPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AActivatedPlatform::OnBeginOverlap);
	
	StartLocation = GetActorLocation();
}

void AActivatedPlatform::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bActivated) return;

	if (
		FVector NewLocation = GetActorLocation(); 
		bReturning && NewLocation.Equals(StartLocation, 0.01f)
	)
	{
		SetActorLocation(StartLocation);
		bReturning = false;
		bActivated = false;
	} 
	else if (bReturning)
	{
		MoveActor(DeltaTime, NewLocation, StartLocation);
	}
	else if (NewLocation.Equals(EndLocation, 0.01f))
	{
		SetActorLocation(EndLocation);
		bReturning = true;
		bActivated = false;
	}
	else
	{
		MoveActor(DeltaTime, NewLocation, EndLocation);
	}
}

void AActivatedPlatform::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (!bActivated && OtherActor && OtherActor->IsA(AGamedevUltimateCharacter::StaticClass()))
	{
		bActivated = true;
	}
}

void AActivatedPlatform::MoveActor(const float DeltaTime, FVector& NewLocation, const FVector& TargetLocation)
{
	FVector Direction = TargetLocation - NewLocation;
	Direction.Normalize();
	NewLocation += Direction * DeltaTime * Speed;
	SetActorLocation(NewLocation);
}
