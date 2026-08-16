// Copyright iBarkGames

#include "FirstSweepActor.h"

#include "Components/TextRenderComponent.h"

AFirstSweepActor::AFirstSweepActor()
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
	TextRenderComponent->SetText(FText::FromString("FirstSweepActor"));
}

void AFirstSweepActor::BeginPlay()
{
	Super::BeginPlay();
	TextRenderComponent->SetVisibility(false);
}

void AFirstSweepActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = StartLocation + GetActorForwardVector() * SweepLength;
	const FCollisionShape SweepSphere = FCollisionShape::MakeSphere(SweepRadius);

	GetWorld()->SweepSingleByChannel(
		HitResult, StartLocation, EndLocation, FQuat::Identity, ECC_Visibility, SweepSphere);

	DrawDebugSphere(GetWorld(), StartLocation, SweepRadius, 16, FColor::Green);
	DrawDebugSphere(GetWorld(), EndLocation, SweepRadius, 16, FColor::Green);
	if (HitResult.bBlockingHit && HitResult.GetActor() != nullptr)
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 0, 1.f);
		DrawDebugSphere(GetWorld(), HitResult.Location, SweepRadius, 16, FColor::Yellow);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, SweepRadius / 5.f, 16, FColor::Red);

		const FString LogText = FString::Printf(TEXT("Hit: Actor:%s, Location:%s, ImpactPoint:%s"),
			*HitResult.GetActor()->GetName(), *HitResult.Location.ToString(), *HitResult.ImpactPoint.ToString());
		TextRenderComponent->SetText(FText::FromString(LogText));
		TextRenderComponent->SetVisibility(true);
		GetWorldTimerManager().SetTimer(
			TextTimer, [this] { TextRenderComponent->SetVisibility(false); }, TextDuration, false);
	}
}
