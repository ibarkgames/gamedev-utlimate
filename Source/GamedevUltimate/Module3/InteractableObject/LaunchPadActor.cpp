// Copyright iBarkGames


#include "LaunchPadActor.h"

#include "GamedevUltimate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"


ALaunchPadActor::ALaunchPadActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(Mesh);
	
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
	BoxComponent->SetNotifyRigidBodyCollision(true);
}

void ALaunchPadActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentHit.AddDynamic(this, &ALaunchPadActor::OnHit);
}

void ALaunchPadActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALaunchPadActor::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		FVector LaunchVelocity = Hit.ImpactNormal;
		LaunchVelocity.Normalize();
		LaunchVelocity *= -LaunchVelocityMagnitude;
		if (bDebug) UE_LOG(
			LogGamedevUltimate, 
			Log, 
			TEXT("Launch character: %s, LaunchVelocity: %s"), *Character->GetName(), *LaunchVelocity.ToString()
		);
		Character->LaunchCharacter(LaunchVelocity, true, true);
	}
	else
	{
		if (bDebug) UE_LOG(
			LogGamedevUltimate, 
			Log, 
			TEXT("LaunchPad unexpected hit actor: %s component: %s"),
			OtherActor ? *OtherActor->GetName() : TEXT("None"),
			OtherComp ? *OtherComp->GetName() : TEXT("None")
		);
	}
}
