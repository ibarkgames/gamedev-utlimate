// Copyright iBarkGames


#include "TrapActor.h"

#include "GamedevUltimate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"


ATrapActor::ATrapActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void ATrapActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrapActor::OnBeginOverlap);
}

void ATrapActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrapActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (OtherActor)
	{
		if (const ACharacter* Character = Cast<ACharacter>(OtherActor); Character)
		{
			const FVector SpawnLocation = Character->GetActorLocation() + SpawnOffset;
			const FRotator Rotation = Character->GetActorRotation();
			AActor* Actor = GetWorld()->SpawnActor(ActorToSpawn, &SpawnLocation, &Rotation);
			if (Actor)
			{
				if (bDebug)
				{
					UE_LOG(LogGamedevUltimate, Log, TEXT("ATrapActor: ActorToSpawn: %s"), *Actor->GetName());
				}
				Actor->SetLifeSpan(5.f);
			}
		}
	}
}
