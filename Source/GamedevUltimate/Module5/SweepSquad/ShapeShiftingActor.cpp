// Copyright iBarkGames

#include "ShapeShiftingActor.h"

AShapeShiftingActor::AShapeShiftingActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShapeShiftingActor::BeginPlay()
{
	Super::BeginPlay();
}

void AShapeShiftingActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const FVector Start = GetActorLocation();
	const FVector End = Start + GetActorForwardVector() * SweepLength;
	FCollisionShape CollisionShape;
	switch (ShapeType)
	{
		case ESweptShapeType::Sphere:
		{
			CollisionShape = FCollisionShape::MakeSphere(SphereShapeParams.Radius);
			break;
		}
		case ESweptShapeType::Box:
			CollisionShape = FCollisionShape::MakeBox(BoxShapeParams.BoxHalfExtent);
			break;
		case ESweptShapeType::Capsule:
			CollisionShape =
				FCollisionShape::MakeCapsule(CapsuleShapeParams.Radius, CapsuleShapeParams.CapsuleHalfHeight);
			break;
	}

	const bool bHit =
		GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_Visibility, CollisionShape);

	// const FColor DebugColor = FColor::Blue;
	// TArray<FVector> Locations;
	// Locations.Add(Start);
	// Locations.Add(End);
	// if (bHit)
	// {
	// 	Locations.Add(HitResult.Location);
	// }

	// for (const FVector& Location : Locations)
	// {
	// 	switch (ShapeType)
	// 	{
	// 		case ESweptShapeType::Sphere:
	// 		{
	// 			DrawDebugSphere(GetWorld(), Location, SphereShapeParams.Radius, 16, DebugColor);
	// 			break;
	// 		}
	// 		case ESweptShapeType::Box:
	// 			DrawDebugBox(GetWorld(), Location, BoxShapeParams.BoxHalfExtent, DebugColor);
	// 			break;
	// 		case ESweptShapeType::Capsule:
	// 			DrawDebugCapsule(GetWorld(), Location, CapsuleShapeParams.CapsuleHalfHeight, CapsuleShapeParams.Radius,
	// 				GetActorQuat(), DebugColor);
	// 			break;
	// 	}
	// }

	auto DrawShape = [&](const FVector& Location, const FColor& Color) {
		switch (ShapeType)
		{
			case ESweptShapeType::Sphere:
			{
				DrawDebugSphere(GetWorld(), Location, SphereShapeParams.Radius, 16, Color);
				break;
			}
			case ESweptShapeType::Box:
				DrawDebugBox(GetWorld(), Location, BoxShapeParams.BoxHalfExtent, Color);
				break;
			case ESweptShapeType::Capsule:
				DrawDebugCapsule(GetWorld(), Location, CapsuleShapeParams.CapsuleHalfHeight, CapsuleShapeParams.Radius,
					GetActorQuat(), Color);
				break;
		}
	};

	DrawShape(Start, FColor::Blue);
	DrawShape(bHit ? HitResult.Location : End, bHit ? FColor::Green : FColor::Red);
}
