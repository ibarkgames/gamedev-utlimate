// Copyright iBarkGames


#include "HitActor.h"

#include "GamedevUltimate.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"


AHitActor::AHitActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh -> SetupAttachment(RootComponent);
}

void AHitActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &AHitActor::OnHit);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AHitActor::OnBeginOverlap);
}

void AHitActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHitActor::OnHit(
	UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, 
	const FHitResult& Hit
)
{
	if (OtherActor &&  OtherActor != this)
	{
		if (bDebug)
			UE_LOG(
				LogGamedevUltimate, 
				Log, 
				TEXT("Hit by actor: %s, component: %s, time: %f"), 
				*OtherActor->GetName(), 
				*OtherComp->GetName(),
				UGameplayStatics::GetTimeSeconds(this)
			);
	}
}

void AHitActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (OtherActor &&  OtherActor != this)
	{
		if (bDebug)
			UE_LOG(
				LogGamedevUltimate, 
				Log, 
				TEXT("Overlap by actor: %s, component: %s, time: %f"), 
				*OtherActor->GetName(), 
				*OtherComp->GetName(),
				UGameplayStatics::GetTimeSeconds(this)
			);
	}
}

