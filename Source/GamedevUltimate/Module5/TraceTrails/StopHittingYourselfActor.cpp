// Copyright iBarkGames

#include "StopHittingYourselfActor.h"

#include "Components/TextRenderComponent.h"
#include "DrawDebugHelpers.h"

AStopHittingYourselfActor::AStopHittingYourselfActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	TextRenderComponent->SetupAttachment(RootComponent);
}

void AStopHittingYourselfActor::BeginPlay()
{
	Super::BeginPlay();

	TextRenderComponent->SetVisibility(false);
}

void AStopHittingYourselfActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = StartLocation + GetActorForwardVector() * TraceDistance;
	FCollisionQueryParams Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);

	if (HitResult.bBlockingHit && HitResult.GetActor() != nullptr)
	{
		DrawDebugLine(GetWorld(), StartLocation, HitResult.GetActor()->GetActorLocation(), FColor::Red, false, -1.f,
			SDPG_World, 1.f);

		TextRenderComponent->SetVisibility(true);
		TextRenderComponent->SetText(FText::FromString(HitResult.GetActor()->GetName()));
	}
	else
	{
		TextRenderComponent->SetVisibility(false);
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, -1.f, SDPG_World, 1.f);
	}
}
