// Copyright iBarkGames

#include "MultiSweepActor.h"

#include "Components/TextRenderComponent.h"

AMultiSweepActor::AMultiSweepActor()
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
	TextRenderComponent->SetText(FText::FromString("MultiSweepActor"));
}

void AMultiSweepActor::BeginPlay()
{
	Super::BeginPlay();
	TextRenderComponent->SetVisibility(false);
}

void AMultiSweepActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FHitResult> HitResults;
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = StartLocation + GetActorForwardVector() * SweepLength;
	const FCollisionShape SweepSphere = FCollisionShape::MakeSphere(SweepRadius);
	FString HitActorNames;

	GetWorld()->SweepMultiByChannel(
		HitResults, StartLocation, EndLocation, FQuat::Identity, ECC_Visibility, SweepSphere);

	DrawDebugSphere(GetWorld(), StartLocation, SweepRadius, 16, FColor::Green);
	DrawDebugSphere(GetWorld(), EndLocation, SweepRadius, 16, FColor::Green);

	for (const FHitResult& HitResult : HitResults)
	{
		if (HitResult.GetActor() != nullptr)
		{
			if (!HitActorNames.IsEmpty())
			{
				HitActorNames += TEXT("\n");
			}
			HitActorNames += HitResult.GetActor()->GetName();

			DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 0, 1.f);
			DrawDebugSphere(GetWorld(), HitResult.Location, SweepRadius, 16, FColor::Yellow);
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, SweepRadius / 5.f, 16, FColor::Red);
		}
	}

	if (!HitActorNames.IsEmpty())
	{
		TextRenderComponent->SetText(FText::FromString(HitActorNames));
		TextRenderComponent->SetVisibility(true);
		GetWorldTimerManager().SetTimer(
			TextTimer, [this] { TextRenderComponent->SetVisibility(false); }, TextDuration, false);
	}
}
