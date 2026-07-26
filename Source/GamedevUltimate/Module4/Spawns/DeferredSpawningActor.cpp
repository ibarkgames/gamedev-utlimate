// Copyright iBarkGames


#include "DeferredSpawningActor.h"

#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


ADeferredSpawningActor::ADeferredSpawningActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(SceneComponent);
}

void ADeferredSpawningActor::BeginPlay()
{
	Super::BeginPlay();
	
	FTransform Transform;
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(ActorClassToSpawn, Transform);
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADeferredSpawningActor::OnBeginOverlap);
}

// Called every frame
void ADeferredSpawningActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADeferredSpawningActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (OtherActor)
		if (const ACharacter* Character = Cast<ACharacter>(OtherActor); Character)
		{
			FTransform Transform = SpawnedActor->GetTransform();
			Transform.SetLocation(BoxComponent->GetComponentLocation() + FVector(0.0f, 0.0f, 100.0f));
			Transform.SetRotation(GetActorRotation().Quaternion());
			UGameplayStatics::FinishSpawningActor(SpawnedActor, Transform);
		}
}

