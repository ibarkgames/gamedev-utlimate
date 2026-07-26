// Copyright iBarkGames


#include "ImpactPointActor.h"

#include "GamedevUltimate.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"


AImpactPointActor::AImpactPointActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void AImpactPointActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &AImpactPointActor::OnHit);
}

void AImpactPointActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AImpactPointActor::OnHit(
	UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, 
	const FHitResult& Hit
)
{
	if (OtherActor && OtherActor != this)
	{
		if (bDebug)
		{
			UE_LOG(LogGamedevUltimate, Log, TEXT("Hit Impact Point: %s, Impact Normal: %s"), *Hit.ImpactPoint.ToString(), *Hit.ImpactNormal.ToString());
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.f, 12, FColor::Red, false, 2.f);
			const FVector HitDirection = Hit.ImpactPoint + Hit.ImpactNormal * 50.f;
			DrawDebugLine(GetWorld(), Hit.ImpactPoint, HitDirection * 1.f,  FColor::Red, false, 2.f);
		}
	}
}

