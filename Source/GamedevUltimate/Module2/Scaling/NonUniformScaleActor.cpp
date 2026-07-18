// Copyright iBarkGames


#include "NonUniformScaleActor.h"

#include "Components/StaticMeshComponent.h"


ANonUniformScaleActor::ANonUniformScaleActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ANonUniformScaleActor::BeginPlay()
{
	Super::BeginPlay();
}

void ANonUniformScaleActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewScale = GetActorScale3D();
	
	if (!bUseInterpolation)
	{
		NewScale.X += DeltaTime * ScaleSpeed.X;
		NewScale.Y += DeltaTime * ScaleSpeed.Y;
		NewScale.Z += DeltaTime * ScaleSpeed.Z;
		
		NewScale.X = FMath::Clamp(NewScale.X, 0.f, MaxScale.X);
		NewScale.Y = FMath::Clamp(NewScale.Y, 0.f, MaxScale.Y);
		NewScale.Z = FMath::Clamp(NewScale.Z, 0.f, MaxScale.Z);
	}
	else
	{
		NewScale.X = FMath::FInterpConstantTo(NewScale.X, MaxScale.X, DeltaTime, ScaleSpeed.X);
		NewScale.Y = FMath::FInterpConstantTo(NewScale.Y, MaxScale.Y, DeltaTime, ScaleSpeed.Y);
		NewScale.Z = FMath::FInterpConstantTo(NewScale.Z, MaxScale.Z, DeltaTime, ScaleSpeed.Z);
	}
	
	SetActorScale3D(NewScale);
}

