// Copyright iBarkGames


#include "AutomaticDoorActor.h"

#include "GamedevUltimate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/Character.h"


AAutomaticDoorActor::AAutomaticDoorActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorFrameMesh");
	DoorFrameMesh->SetupAttachment(RootComponent);
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	DoorMesh->SetupAttachment(DoorFrameMesh);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void AAutomaticDoorActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAutomaticDoorActor::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AAutomaticDoorActor::OnEndOverlap);
	
	ClosedLocation = DoorMesh->GetRelativeLocation();
	OpenLocation = DoorMesh->GetRelativeLocation();
	OpenLocation.Z -= DoorTravellingDistance;
	
	float MinTime{0.f};
	float MaxTime{0.f};
	if (SpeedCurve)
	{
		SpeedCurve->GetTimeRange(MinTime, MaxTime);
		SpeedCurveLength = MaxTime - MinTime;
	}
}

void AAutomaticDoorActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = DoorMesh->GetRelativeLocation();
	// descending
	if (DoorState == EDoorState::Idle && OverlappingActors.Num() > 0 && NewLocation.Z - OpenLocation.Z > 0.1f)
	{
		Time = 0.f;
		DoorState = EDoorState::Descending;
	}
	else if (DoorState == EDoorState::Descending && OverlappingActors.Num() > 0 && NewLocation.Z - OpenLocation.Z <= 0.1f)
	{
		DoorMesh->SetRelativeLocation(OpenLocation);
		DoorState = EDoorState::Idle;
	}
	else if (DoorState == EDoorState::Descending && OverlappingActors.Num() == 0)
	{
		Time = 0.f;
		DoorState = EDoorState::Elevating; 
	}
	// elevating
	else if (DoorState == EDoorState::Idle && OverlappingActors.Num() == 0 && ClosedLocation.Z - NewLocation.Z > 0.1f)
	{
		Time = 0.f;
		DoorState = EDoorState::Elevating; 
	}
	else if (DoorState == EDoorState::Elevating && OverlappingActors.Num() == 0 && ClosedLocation.Z - NewLocation.Z <= 0.1f)
	{
		DoorMesh->SetRelativeLocation(ClosedLocation);
		DoorState = EDoorState::Idle;
	}
	else if (DoorState == EDoorState::Elevating && OverlappingActors.Num() > 0)
	{
		Time = 0.f;
		DoorState = EDoorState::Descending; 
	}
	
	if (DoorState == EDoorState::Descending)
	{
		CalculateNextDoorLocation(DeltaTime, NewLocation, OpenLocation);
		DoorMesh->SetRelativeLocation(NewLocation);
	}
	else if (DoorState == EDoorState::Elevating)
	{
		CalculateNextDoorLocation(DeltaTime, NewLocation, ClosedLocation);
		DoorMesh->SetRelativeLocation(NewLocation);
	}
}

void AAutomaticDoorActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (OtherActor && OtherActor != this && !OverlappingActors.Contains(OtherActor))
	{
		OverlappingActors.AddUnique(OtherActor);
	}
}

void AAutomaticDoorActor::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex
)
{
	if (OtherActor && OtherActor != this && OverlappingActors.Contains(OtherActor))
	{
		OverlappingActors.Remove(OtherActor);
	}
}

void AAutomaticDoorActor::CalculateNextDoorLocation(
	const float DeltaTime, 
	FVector& NewLocation,
	const FVector& TargetLocation
)
{
	Time += DeltaTime;
	const float Speed = SpeedCurve ? SpeedCurve->GetFloatValue(Time) : 0.f;
	NewLocation = FMath::VInterpConstantTo(NewLocation, TargetLocation, DeltaTime, Speed);
}
