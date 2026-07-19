// Copyright iBarkGames


#include "OverlapPlayerActor.h"

#include "GamedevUltimate.h"
#include "GamedevUltimateCharacter.h"
#include "Components/BoxComponent.h"


AOverlapPlayerActor::AOverlapPlayerActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(SceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
	
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AOverlapPlayerActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AOverlapPlayerActor::OnComponentBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AOverlapPlayerActor::OnComponentEndOverlap);
}

void AOverlapPlayerActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOverlapPlayerActor::OnComponentBeginOverlap(
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
		if (const AGamedevUltimateCharacter* Player = Cast<AGamedevUltimateCharacter>(OtherActor); Player)
		{
			if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("Hello %s!"), *Player->GetName())
		}
	}
}

void AOverlapPlayerActor::OnComponentEndOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	if (OtherActor && OtherActor != this)
	{
		if (const AGamedevUltimateCharacter* Player = Cast<AGamedevUltimateCharacter>(OtherActor); Player)
		{
			if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("Bye %s!"), *Player->GetName())
		}
	}
}

