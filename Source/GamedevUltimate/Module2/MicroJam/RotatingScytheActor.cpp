// Copyright iBarkGames


#include "RotatingScytheActor.h"

#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"


ARotatingScytheActor::ARotatingScytheActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);

	BeamMesh = CreateDefaultSubobject<UStaticMeshComponent>("BeamMesh");
	BeamMesh->SetupAttachment(RootComponent);
	
	AdaptorMesh = CreateDefaultSubobject<UStaticMeshComponent>("AdaptorMesh");
	AdaptorMesh->SetupAttachment(BeamMesh);
}

void ARotatingScytheActor::BeginPlay()
{
	Super::BeginPlay();
	Start = GetActorLocation();
	BeamInitialLocation = BeamMesh->GetRelativeLocation();

	const APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (APawn* PlayerPawn = PC ? PC->GetPawn() : nullptr)
	{
		TargetActor = Cast<AActor>(PlayerPawn);
	}
}

void ARotatingScytheActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!TargetActor.IsValid())
	{
		return;
	}

	if (
		const float DistanceToTarget = CalculateDistanceToTarget();
		CurrentState == ETrapState::Idle && DistanceToTarget < ActivationDistance
	)
	{
		GEngine->AddOnScreenDebugMessage(25, 1.f, FColor::Green,TEXT("Start Elevating"));
		CurrentState = ETrapState::Elevating;
	}
	// else if (CurrentState == ETrapState::Idle && DistanceToTarget >= ActivationDistance)
	// {
		// GEngine->AddOnScreenDebugMessage(25, 1.f, FColor::Green,TEXT("Start Descending"));
		// CurrentState = ETrapState::Descending;
	// }
	else if (CurrentState == ETrapState::Elevating)
	{
		Elevate(DeltaTime);
	}
	else if (CurrentState == ETrapState::Descending)
	{
		Descend(DeltaTime);
	}
	else if (CurrentState == ETrapState::Moving)
	{
		Move(DeltaTime);
	}
}

void ARotatingScytheActor::Elevate(const float DeltaTime)
{
	if (FVector NewLocation = BeamMesh->GetRelativeLocation(); FMath::Abs(MovingElevation - NewLocation.Z) < 0.1f)
	{
		GEngine->AddOnScreenDebugMessage(25, 1.f, FColor::Green,TEXT("Start Moving"));
		CurrentState = ETrapState::Moving;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(27, 1.f, FColor::Green,
		                                 FString::Printf(TEXT("Elevating. Actor location: %s"),
		                                                 *NewLocation.ToString())
		);
		NewLocation.Z = FMath::FInterpConstantTo(NewLocation.Z, MovingElevation, DeltaTime, ElevationSpeed);
		BeamMesh->SetRelativeLocation(NewLocation);
	}
}

void ARotatingScytheActor::Descend(const float DeltaTime)
{
	if (FVector NewScale = BeamMesh->GetRelativeLocation(); FMath::Abs(NewScale.Z - BeamInitialLocation.Z) < 0.1f)
	{
		GEngine->AddOnScreenDebugMessage(25, 1.f, FColor::Green,TEXT("Stop"));
		CurrentState = ETrapState::Idle;
		BeamMesh->SetRelativeLocation(BeamInitialLocation);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(29, 1.f, FColor::Green,
		                                 FString::Printf(TEXT("Descending. Actor scale: %s"),
		                                                 *NewScale.ToString())
		);
		NewScale.Z = FMath::FInterpConstantTo(NewScale.Z, BeamInitialLocation.Z, DeltaTime, ElevationSpeed);
		BeamMesh->SetRelativeLocation(NewScale);
	}
}

void ARotatingScytheActor::Move(const float DeltaTime)
{
	Time +=	DeltaTime;
	RotationTime += DeltaTime;
	
	const float CurveDuration = SpeedCurve->FloatCurve.GetLastKey().Time;
	const float ClampedTime = FMath::Clamp(Time, 0.f, CurveDuration);
	const float Alpha = SpeedCurve->GetFloatValue(ClampedTime); // curve now represents 0..1 alpha, not raw speed

	const FVector TargetStart = bIsReturning ? End : Start;
	const FVector TargetEnd = bIsReturning ? Start : End;

	FVector NewLocation = FMath::Lerp(TargetStart, TargetEnd, Alpha);
	SetActorLocation(NewLocation);

	if (Alpha >= 1.f)
	{
		bIsReturning = !bIsReturning;
		Time = 0.f;

		if (!bIsReturning && CalculateDistanceToTarget() > ActivationDistance)
		{
			CurrentState = ETrapState::Descending;
			RotationTime = 0.f;
		}
	}

	RotationSpeed = RotationSpeedCurve->GetFloatValue(RotationTime);
	FRotator NewRotation = AdaptorMesh->GetRelativeRotation();
	NewRotation.Yaw += RotationSpeed * DeltaTime;
	AdaptorMesh->SetRelativeRotation(NewRotation);
}

float ARotatingScytheActor::CalculateDistanceToTarget() const
{
	FVector DirectionToTarget = TargetActor->GetActorLocation() - GetActorLocation();
	DirectionToTarget.Z = 0.f;
	return DirectionToTarget.Length();
}
