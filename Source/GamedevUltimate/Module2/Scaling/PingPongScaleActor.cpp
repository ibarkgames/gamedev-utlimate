// Copyright iBarkGames


#include "PingPongScaleActor.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"


APingPongScaleActor::APingPongScaleActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void APingPongScaleActor::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultUniformScale = GetActorScale3D().X;
	DefaultNonUniformScale = GetActorScale3D();
}

void APingPongScaleActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewScale;
	if (bUniformScale)
	{
		NewScale = UniformScale(DeltaTime);
	}
	else
	{
		NewScale = NonUniformScale(DeltaTime);
	}
	SetActorScale3D(NewScale);
}

FVector APingPongScaleActor::UniformScale(const float DeltaTime)
{
	const float X = GetActorScale3D().X;
	float ScalingComponent;
	if (bIsReturning)
	{
		ScalingComponent = FMath::FInterpConstantTo(X, DefaultUniformScale, DeltaTime, ScalingSpeed);
		if (ScalingComponent <= DefaultUniformScale)
		{
			bIsReturning = false;
		}
	}
	else
	{
		ScalingComponent = FMath::FInterpConstantTo(X, UniformMaxScale, DeltaTime, ScalingSpeed);
		if (ScalingComponent >= UniformMaxScale)
		{
			bIsReturning = true;
		}
	}
	return FVector{ScalingComponent, ScalingComponent, ScalingComponent};
}

FVector APingPongScaleActor::NonUniformScale(float DeltaTime)
{
	FVector NewScale = GetActorScale3D();
	if (bIsReturning)
	{
		NewScale = FMath::VInterpConstantTo(NewScale, DefaultNonUniformScale, DeltaTime, ScalingSpeed);
		if (NewScale.Length() <= DefaultNonUniformScale.Length())
		{
			bIsReturning = false;
		}
	}
	else
	{
		NewScale = FMath::VInterpConstantTo(NewScale, NonUniformMaxScale, DeltaTime, ScalingSpeed);
		if (NewScale.Length() >= NonUniformMaxScale.Length())
		{
			bIsReturning = true;
		}
	}
	return NewScale;
}
