// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShapeShiftingActor.generated.h"

// Goal: Experiment with other collision shape types: Box and Capsule
// Spheres are not the only shape you can sweep.
// Create an Actor and experiment with FCollisionShape::MakeBox and FCollisionShape::MakeCapsule.
// Create EditAnywhere variables for the shape sizes. (Radius, box extents, capsule half height)
// Draw matching debug shapes so you can see what you are sweeping.(DrawDebugBox, DrawDebugCapsule)

// Test all 3 shapes against the same obstacles and observe the
// differences.Bonus :
// Create an enum type that lets you pick the shape type from the editor.

UENUM(BlueprintType)
enum class ESweptShapeType : uint8
{
	Sphere,
	Box,
	Capsule
};

USTRUCT()
struct FSphereShapeParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Radius{ 50.f };
};

USTRUCT()
struct FBoxShapeParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FVector BoxHalfExtent{ 25.f, 25.f, 10.f };
};

USTRUCT()
struct FCapsuleShapeParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Radius{ 50.f };

	UPROPERTY(EditAnywhere)
	float CapsuleHalfHeight{ 50.f };
};

UCLASS()
class GAMEDEVULTIMATE_API AShapeShiftingActor : public AActor
{
	GENERATED_BODY()

public:
	AShapeShiftingActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "ShapeShiftActor", meta = (AllowPrivateAccess = "true"))
	float SweepLength{ 1000.f };

	UPROPERTY(EditAnywhere, Category = "ShapeShiftActor", meta = (AllowPrivateAccess = "true"))
	ESweptShapeType ShapeType{ ESweptShapeType::Sphere };

	UPROPERTY(EditAnywhere, Category = "ShapeShiftActor",
		meta = (AllowPrivateAccess = "true", EditCondition = "ShapeType == ESweptShapeType::Sphere",
			EditConditionHides))
	FSphereShapeParams SphereShapeParams;

	UPROPERTY(EditAnywhere, Category = "ShapeShiftActor",
		meta = (AllowPrivateAccess = "true", EditCondition = "ShapeType == ESweptShapeType::Box", EditConditionHides))
	FBoxShapeParams BoxShapeParams;

	UPROPERTY(EditAnywhere, Category = "ShapeShiftActor",
		meta = (AllowPrivateAccess = "true", EditCondition = "ShapeType == ESweptShapeType::Capsule",
			EditConditionHides))
	FCapsuleShapeParams CapsuleShapeParams;
};
