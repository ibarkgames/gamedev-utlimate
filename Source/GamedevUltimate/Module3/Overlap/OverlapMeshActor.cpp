// Copyright iBarkGames


#include "OverlapMeshActor.h"

#include "GamedevUltimate.h"
#include "Components/StaticMeshComponent.h"


AOverlapMeshActor::AOverlapMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void AOverlapMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AOverlapMeshActor::OnComponentBeginOverlap);
	Mesh->OnComponentEndOverlap.AddDynamic(this, &AOverlapMeshActor::OnComponentEndOverlap);
}

void AOverlapMeshActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOverlapMeshActor::OnComponentBeginOverlap(
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
				TEXT("StaticMesh BeginOverlap with actor: %s, component: %s"), *OtherActor->GetName(), *OtherComp->GetName()
			);
	}
}

void AOverlapMeshActor::OnComponentEndOverlap(
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
				TEXT("StaticMesh EndOverlap with actor: %s, component: %s"), *OtherActor->GetName(), *OtherComp->GetName()
			);
	}
}

