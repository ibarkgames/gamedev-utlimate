// Copyright iBarkGames


#include "PhysicsHitActor.h"

#include "GamedevUltimate.h"
#include "Components/StaticMeshComponent.h"


APhysicsHitActor::APhysicsHitActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void APhysicsHitActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &APhysicsHitActor::OnHit);
}

void APhysicsHitActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicsHitActor::OnHit(
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
			if (const float HitImpulse = NormalImpulse.Size(); HitImpulse > 100000.f)
			{
				UE_LOG(LogGamedevUltimate, Log, TEXT("HardHit: Hit Impact Point: %s Impulse: %f"), *Hit.ImpactPoint.ToString(), HitImpulse);
			}
			else
			{
				UE_LOG(LogGamedevUltimate, Log, TEXT("SoftHit: Hit Impact Point: %s Impulse: %f"), *Hit.ImpactPoint.ToString(), HitImpulse);
			}
		}
	}
}

