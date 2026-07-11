// Copyright iBarkGames


#include "SpeedCurvesActor.h"

#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"


ASpeedCurvesActor::ASpeedCurvesActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ASpeedCurvesActor::BeginPlay()
{
	Super::BeginPlay();
	if (SpeedCurve == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Speed Curve is nullptr"));	
	}
}

void ASpeedCurvesActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SpeedCurve == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Speed Curve is nullptr"));	
		return;
	}
	
	const FRichCurveKey LastKey = SpeedCurve->FloatCurve.GetLastKey();
	TimeInCurve = FMath::Fmod(DeltaTime + TimeInCurve, LastKey.Time);
	const float Speed = SpeedCurve->GetFloatValue(TimeInCurve);
	
	FVector NewLocation = GetActorLocation();
	if (bIsReturning)
	{
		NewLocation = FMath::VInterpConstantTo(NewLocation, Start, Speed, DeltaTime);
		if (NewLocation.Equals(Start))
		{
			bIsReturning = false;
		}
	}
	else
	{
		NewLocation = FMath::VInterpConstantTo(NewLocation, End, Speed, DeltaTime);
		if (NewLocation.Equals(End))
		{
			bIsReturning = true;
		}
	}
	SetActorLocation(NewLocation);
}

