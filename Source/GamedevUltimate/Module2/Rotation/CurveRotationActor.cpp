// Copyright iBarkGames


#include "CurveRotationActor.h"

#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Curves/RichCurve.h"


ACurveRotationActor::ACurveRotationActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ACurveRotationActor::BeginPlay()
{
	Super::BeginPlay();
	if (SpeedCurve == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Speed Curve is nullptr"));	
	}
}

void ACurveRotationActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (SpeedCurve == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Speed Curve is nullptr"));	
		return;
	}
	
	const FRichCurveKey LastKey = SpeedCurve->FloatCurve.GetLastKey();
	TimeInCurve = FMath::Fmod(DeltaTime + TimeInCurve, LastKey.Time);
	const float RotationSpeed = SpeedCurve->GetFloatValue(TimeInCurve);
	
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(NewRotation);
}

