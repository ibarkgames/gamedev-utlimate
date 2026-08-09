// Copyright iBarkGames

#include "ObjectTypeTraceActor.h"

#include "Components/TextRenderComponent.h"

AObjectTypeTraceActor::AObjectTypeTraceActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	TextRenderComponent->SetupAttachment(RootComponent);
	TextRenderComponent->SetTextRenderColor(FColor::Black);
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TextRenderComponent->SetRelativeRotation(FRotator(0.0f, -45.0f, 0.0f));
	TextRenderComponent->SetText(FText::FromString("ObjectTypeTraceActor"));
}

void AObjectTypeTraceActor::BeginPlay()
{
	Super::BeginPlay();

	TextRenderComponent->SetVisibility(false);
}

void AObjectTypeTraceActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = StartLocation + GetActorForwardVector() * TraceDistance;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByObjectType(
		HitResult, StartLocation, EndLocation, ObjectQueryParams, CollisionQueryParams);

	FColor Color = FColor::Green;
	if (HitResult.bBlockingHit && HitResult.GetActor() != nullptr)
	{
		TextRenderComponent->SetVisibility(true);
		TextRenderComponent->SetText(FText::FromString(HitResult.GetActor()->GetName()));
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 15.f, 16, FColor::Cyan);
		Color = FColor::Red;
	}
	else
	{
		const FVector NewLocation = StartLocation + GetActorForwardVector() * Speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, Color);
}
