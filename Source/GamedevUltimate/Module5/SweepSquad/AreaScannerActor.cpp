// Copyright iBarkGames

#include "AreaScannerActor.h"

#include "Components/TextRenderComponent.h"
#include "Engine/OverlapResult.h"

AAreaScannerActor::AAreaScannerActor()
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
	TextRenderComponent->SetText(FText::FromString("AreaScannerActor"));
}

void AAreaScannerActor::BeginPlay()
{
	Super::BeginPlay();

	TextRenderComponent->SetVisibility(false);
}

void AAreaScannerActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FOverlapResult> OverlapResults;
	const FVector Location = GetActorLocation();

	GetWorld()->OverlapMultiByChannel(
		OverlapResults, Location, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(SweepRadius));

	DrawDebugSphere(GetWorld(), Location, SweepRadius, 16, FColor::Red);

	FString OverlapActorNames;
	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (OverlapResult.GetActor() != nullptr)
		{
			if (!OverlapActorNames.IsEmpty())
			{
				OverlapActorNames += TEXT("\n");
			}
			OverlapActorNames += OverlapResult.GetActor()->GetName();

			DrawDebugSphere(
				GetWorld(), OverlapResult.GetActor()->GetActorLocation(), DebugSphereRadius, 16, FColor::Yellow);
		}
	}

	if (!OverlapActorNames.IsEmpty())
	{
		TextRenderComponent->SetText(FText::FromString(OverlapActorNames));
		TextRenderComponent->SetVisibility(true);
		GetWorldTimerManager().SetTimer(
			TextTimer, [this] { TextRenderComponent->SetVisibility(false); }, TextDuration, false);
	}
}
