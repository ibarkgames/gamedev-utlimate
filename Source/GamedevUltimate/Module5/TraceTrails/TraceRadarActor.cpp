// Copyright iBarkGames

#include "TraceRadarActor.h"

#include "Components/TextRenderComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATraceRadarActor::ATraceRadarActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	TextRenderComponent->SetupAttachment(RootComponent);
	TextRenderComponent->SetTextRenderColor(FColor::Red);
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TextRenderComponent->SetRelativeRotation(FRotator(0.0f, -45.0f, 0.0f));
	TextRenderComponent->SetText(FText::FromString("TraceRadarActor"));
}

void ATraceRadarActor::BeginPlay()
{
	Super::BeginPlay();

	TextRenderComponent->SetVisibility(false);
}

void ATraceRadarActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += RotatingSpeed * DeltaTime;
	if (NewRotation.Yaw > 360.f)
		NewRotation.Yaw -= 360.f;
	SetActorRotation(NewRotation);

	FHitResult HitResult;
	const FVector StartLocation = StaticMeshComponent->GetComponentLocation(); // FVector(0.0f, 0.0f, TraceZOffset);
	const FVector EndLocation = StartLocation + GetActorForwardVector() * TraceDistance;
	FCollisionObjectQueryParams CollisionObjectParams;
	CollisionObjectParams.AddObjectTypesToQuery(ECC_Pawn);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByObjectType(
		HitResult, StartLocation, EndLocation, CollisionObjectParams, CollisionQueryParams);

	FColor TraceColor = FColor::Green;
	if (HitResult.bBlockingHit && HitResult.GetActor() != nullptr)
	{
		const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (HitResult.GetActor() == PlayerPawn)
		{
			TextRenderComponent->SetVisibility(true);

			const FString WarningText =
				FString::Printf(TEXT("Intruder detected! Name: %s"), *HitResult.GetActor()->GetName());
			TextRenderComponent->SetText(FText::FromString(WarningText));
			GetWorldTimerManager().SetTimer(
				WarningTimer, [this] { TextRenderComponent->SetVisibility(false); }, WarningMessageTime, false);
			TraceColor = FColor::Red;
		}
	}
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, TraceColor);
}
