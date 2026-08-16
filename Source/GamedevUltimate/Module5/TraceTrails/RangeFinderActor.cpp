// Copyright iBarkGames

#include "RangeFinderActor.h"

#include "GamedevUltimate.h"
#include "Components/TextRenderComponent.h"
#include "DrawDebugHelpers.h"

ARangeFinderActor::ARangeFinderActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	TextRenderComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARangeFinderActor::BeginPlay()
{
	Super::BeginPlay();

	TextRenderComponent->SetVisibility(false);
}

void ARangeFinderActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = StartLocation + GetActorForwardVector() * TraceDistance;
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);

	if (HitResult.GetActor() != nullptr && HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), StartLocation, HitResult.GetActor()->GetActorLocation(), FColor::Red, false, -1.f,
			SDPG_World, 1.f);
		TextRenderComponent->SetVisibility(true);
		TextRenderComponent->SetText(FText::AsNumber(HitResult.Distance));
		if (bDebug)
			UE_LOG(LogGamedevUltimate, Log, TEXT("Distance: %f / %f"), HitResult.Distance,
				(HitResult.GetActor()->GetActorLocation() - StartLocation).Length());
	}
	else
	{
		TextRenderComponent->SetVisibility(false);
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, -1.f, SDPG_World, 1.f);
	}
}
