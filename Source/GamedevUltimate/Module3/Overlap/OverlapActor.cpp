// Copyright iBarkGames


#include "OverlapActor.h"

#include "GamedevUltimate.h"
#include "Components/BoxComponent.h"


AOverlapActor::AOverlapActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionBox->SetupAttachment(RootComponent);
	
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
}

void AOverlapActor::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AOverlapActor::OnComponentBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AOverlapActor::OnComponentEndOverlap);
}

void AOverlapActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOverlapActor::OnComponentBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
	)
{
	if (OtherActor && OtherActor != this)
	{
		if (bDebug)
			UE_LOG(
				LogGamedevUltimate,
				Log, 
				TEXT("%s entered the box (component: %s)"), *OtherActor->GetName(), *OtherComp->GetName()
			);
	}
}

void AOverlapActor::OnComponentEndOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex
)
{
	if (OtherActor && OtherActor != this)
	{
		if (bDebug)
			UE_LOG(
				LogGamedevUltimate, 
				Log, 
				TEXT("%s left the box! (component: %s)"),
				*OtherActor->GetName(),
				*OtherComp->GetName()
			);
	}
}

