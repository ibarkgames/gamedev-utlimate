// Copyright iBarkGames

#include "RotatedSweepActor.h"

#include "Components/ArrowComponent.h"

ARotatedSweepActor::ARotatedSweepActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(RootComponent);
}

void ARotatedSweepActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARotatedSweepActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const FVector Start = GetActorLocation();
	const FVector End = Start + GetActorForwardVector() * SweepLength;
	const FQuat Rotation = ArrowComponent->GetComponentRotation().Quaternion();

	const bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End, Rotation, ECC_Visibility, FCollisionShape::MakeBox(BoxShapeParams.BoxHalfExtent));

	DrawDebugBox(GetWorld(), Start, BoxShapeParams.BoxHalfExtent, Rotation, FColor::Green);
	if (bHit)
		DrawDebugBox(GetWorld(), HitResult.Location, BoxShapeParams.BoxHalfExtent, Rotation, FColor::Red);
	DrawDebugBox(GetWorld(), End, BoxShapeParams.BoxHalfExtent, Rotation, FColor::Green);
}
