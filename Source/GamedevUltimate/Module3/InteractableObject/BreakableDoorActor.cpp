// Copyright iBarkGames


#include "BreakableDoorActor.h"

#include "GamedevUltimate.h"
#include "Components/StaticMeshComponent.h"


ABreakableDoorActor::ABreakableDoorActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorFrameMesh");
	DoorFrameMesh->SetupAttachment(RootComponent);
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	DoorMesh->SetupAttachment(DoorFrameMesh);
}

void ABreakableDoorActor::BeginPlay()
{
	Super::BeginPlay();
	
	DoorMesh->OnComponentHit.AddDynamic(this, &ABreakableDoorActor::OnHit);
}

void ABreakableDoorActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABreakableDoorActor::OnHit(
	UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, 
	const FHitResult& Hit
)
{
	if (OtherActor && OtherActor != this)
	{
		const FVector OtherVelocity = OtherComp && OtherComp->IsSimulatingPhysics()
			? OtherComp->GetPhysicsLinearVelocity()
			: OtherActor->GetVelocity();
		
		if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("ABreakableDoorActor::OnHit ImpactNormal: %s, Velocity: %s, Length: %f"), *Hit.ImpactNormal.ToString(), *OtherVelocity.ToString(), OtherVelocity.Length());
		
		if (OtherVelocity.Length() > MinimumVelocity)
		{
			DoorMesh->SetSimulatePhysics(true);
			DoorMesh->AddImpulse(OtherVelocity * ImpulseScale, NAME_None, true);
		}
	}
}


