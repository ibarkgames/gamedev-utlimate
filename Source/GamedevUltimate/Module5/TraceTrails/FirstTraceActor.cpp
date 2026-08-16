// Copyright iBarkGames

#include "FirstTraceActor.h"

#include "Components/TextRenderComponent.h"
#include "DrawDebugHelpers.h"

AFirstTraceActor::AFirstTraceActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	TextRenderComponent->SetupAttachment(RootComponent);
}

void AFirstTraceActor::BeginPlay()
{
	Super::BeginPlay();
	TextRenderComponent->SetVisibility(false);
}

void AFirstTraceActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult HitResult = FHitResult();
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = StartLocation + GetActorForwardVector() * TraceDistance;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);
	
	const FColor LineColor = bHit ? FColor::Red : FColor::Green;
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, LineColor, false, -1.f, SDPG_World, 1.0f);
	
	if (bHit && HitResult.GetActor() != nullptr)
	{
		TextRenderComponent->SetText(FText::FromString(HitResult.GetActor()->GetName()));
		TextRenderComponent->SetVisibility(true);
		
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 7.5f, 16, FColor::Yellow, false, -1.f, SDPG_World, 0.5f);
	}
	else
	{
		TextRenderComponent->SetVisibility(false);
	}
}

