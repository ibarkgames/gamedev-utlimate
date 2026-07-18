// Copyright iBarkGames


#include "MovingObstacleActor.h"

#include "GamedevUltimate.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Engine/Engine.h"
#include "Module2/Scaling/RandomizeScaleActor.h"


AMovingObstacleActor::AMovingObstacleActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);

	OuterCircle = CreateDefaultSubobject<UStaticMeshComponent>("OuterCircle");
	OuterCircle->SetupAttachment(RootComponent);
	
	InnerCircle = CreateDefaultSubobject<UStaticMeshComponent>("InnerCircle");
	InnerCircle->SetupAttachment(RootComponent);
	
	Arrows = CreateDefaultSubobject<UStaticMeshComponent>("Arrows");
	Arrows->SetupAttachment(RootComponent);
}

void AMovingObstacleActor::BeginPlay()
{
	Super::BeginPlay();

	if (Targets.Num() == 0)
	{
		UE_LOG(LogGamedevUltimate, Error, TEXT("No Targets found"));
	}
	if (Targets.Num() == 1)
	{
		UE_LOG(LogGamedevUltimate, Error, TEXT("Not Enough Targets found"));
	}
	if (!IsValid(SpeedCurve))
	{
		UE_LOG(LogGamedevUltimate, Error, TEXT("Invalid SpeedCurve"));
	}
	
	BaseArrowsScale = Arrows->GetRelativeScale3D();
}

void AMovingObstacleActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Targets.Num() < 2 || !IsValid(SpeedCurve))
	{
		return;
	}

	Time += DeltaTime;
	FVector NewLocation = CalculateBasicMovement(DeltaTime);
	
	const float OscillationAlpha = FMath::Sin(Time * OscillationAmplitude);
	const float ZAdjustment = FMath::Lerp(0.f, VerticalOscillation, OscillationAlpha);
	NewLocation.Z += ZAdjustment * DeltaTime;
	
	SetActorLocation(NewLocation);
	
	FRotator NewRotation = InnerCircle->GetRelativeRotation();
	NewRotation.Yaw += RotationSpeed * DeltaTime;
	InnerCircle->SetRelativeRotation(NewRotation);
	
	const float YawRadians = FMath::DegreesToRadians(NewRotation.Yaw);
	const float Alpha = (1.f + FMath::Cos(2.f * YawRadians)) / 2.f;
	
	const float NewScaleComponent = FMath::Lerp(MinScale, MaxScale, Alpha);
	const FVector NewScale = BaseArrowsScale * FVector{NewScaleComponent, NewScaleComponent, 1.f};
	Arrows->SetRelativeScale3D(NewScale);
}

FVector AMovingObstacleActor::CalculateBasicMovement(const float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	const FVector TargetLocation = Targets[NextTargetIndex]->GetActorLocation();
	if (NewLocation.Equals(TargetLocation, 25.f) && !bWaiting)
	{
		bWaiting = true;
		NextTargetIndex = (NextTargetIndex + 1) % Targets.Num();
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			[this]() { bWaiting = false; },
			WaitingTimeOnTarget,
			false
		);
	}

	if (!bWaiting)
	{
		const float SpeedCurveLength = SpeedCurve->FloatCurve.GetLastKey().Time;
		const float TimeInCurve = FMath::Fmod(Time, SpeedCurveLength);
		const float MovingSpeed = SpeedCurve->GetFloatValue(TimeInCurve);
		
		FVector Direction = TargetLocation - NewLocation;
		Direction.Normalize();
		NewLocation += Direction * MovingSpeed * DeltaTime;
	}
	
	return NewLocation;
}
