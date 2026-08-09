// Copyright iBarkGames

#include "XRayTraceActor.h"

#include "Components/TextRenderComponent.h"

AXRayTraceActor::AXRayTraceActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	TextRenderComponent->SetupAttachment(RootComponent);
	TextRenderComponent->SetTextRenderColor(FColor::Black);
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TextRenderComponent->SetRelativeRotation(FRotator(0.0f, -45.0f, 0.0f));
}

void AXRayTraceActor::BeginPlay()
{
	Super::BeginPlay();
	TextRenderComponent->SetVisibility(false);
}

void AXRayTraceActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FHitResult> HitResults;
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = StartLocation + GetActorForwardVector() * TraceDistance;
	const bool bHit = GetWorld()->LineTraceMultiByChannel(HitResults, StartLocation, EndLocation, ECC_Visibility);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, bHit ? FColor::Red : FColor::Green);

	if (bHit)
	{
		TextRenderComponent->SetVisibility(true);
		TextRenderComponent->SetText(FText::AsNumber(HitResults.Num()));
	}

	for (auto HitResult : HitResults)
	{
		DrawDebugSphere(
			GetWorld(), HitResult.ImpactPoint, 15.f, 16, HitResult.bBlockingHit ? FColor::Red : FColor::Yellow);
	}
}
