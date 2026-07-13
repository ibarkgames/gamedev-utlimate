// Copyright iBarkGames


#include "CurveScaleActor.h"

#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Curves/RichCurve.h"


ACurveScaleActor::ACurveScaleActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ACurveScaleActor::BeginPlay()
{
	Super::BeginPlay();
	if (SpeedCurve == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Speed Curve is nullptr"));	
	}
	DefaultScale = GetActorScale3D();
}

void ACurveScaleActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (SpeedCurve == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Speed Curve is nullptr"));	
		return;
	}
	
	const FRichCurveKey LastKey = SpeedCurve->FloatCurve.GetLastKey();
	TimeInCurve = FMath::Fmod(DeltaTime + TimeInCurve, LastKey.Time);
	float Speed = SpeedCurve->GetFloatValue(TimeInCurve);
	
	FVector NextScale = GetActorScale3D();
	if (bIsReturning)
	{
		NextScale = FMath::VInterpConstantTo(NextScale, DefaultScale, DeltaTime, Speed);
		if (NextScale.Length() <= DefaultScale.Length())
		{
			bIsReturning = false;
		}
	}
	else
	{
		NextScale = FMath::VInterpConstantTo(NextScale, MaxScale, DeltaTime, Speed);
		if (NextScale.Length() >= MaxScale.Length())
		{
			bIsReturning = true;
		}
	}
	SetActorScale3D(NextScale);
}

