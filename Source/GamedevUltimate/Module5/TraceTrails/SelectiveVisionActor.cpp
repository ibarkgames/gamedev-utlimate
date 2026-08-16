// Copyright iBarkGames

#include "SelectiveVisionActor.h"

#include "Components/TextRenderComponent.h"
#include "DrawDebugHelpers.h"

ASelectiveVisionActor::ASelectiveVisionActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	TextRenderComponent->SetupAttachment(RootComponent);
}

void ASelectiveVisionActor::BeginPlay()
{
	Super::BeginPlay();

	TextRenderComponent->SetVisibility(false);
}

void ASelectiveVisionActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = StartLocation + GetActorForwardVector() * TraceDistance;

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

	if (HitResult.bBlockingHit && HitResult.GetActor() != nullptr)
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, SDPG_World, 1.f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 15.f, 16, FColor::Yellow, false, -1.f, SDPG_World, 0.5f);

		TextRenderComponent->SetVisibility(true);
		TextRenderComponent->SetText(FText::FromString(HitResult.GetActor()->GetName()));
	}
	else
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, -1.f, SDPG_World, 1.f);
		TextRenderComponent->SetVisibility(false);
	}
}
