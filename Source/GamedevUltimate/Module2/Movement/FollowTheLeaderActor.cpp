// Copyright iBarkGames


#include "FollowTheLeaderActor.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


AFollowTheLeaderActor::AFollowTheLeaderActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void AFollowTheLeaderActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (TargetActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Actor is nullptr"));
	}
}

void AFollowTheLeaderActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (TargetActor == nullptr)
	{
		return;
	}
	
	FVector NewLocation = GetActorLocation();
	NewLocation = FMath::VInterpConstantTo(NewLocation, TargetActor->GetActorLocation(), DeltaTime, MovingSpeed);
	if ((TargetActor->GetActorLocation() - NewLocation).Length() > MinimumDistanceFromTarget)
	{
		SetActorLocation(NewLocation);
	}
}
