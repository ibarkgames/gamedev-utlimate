// Copyright iBarkGames


#include "FirstSpawnActor.h"

#include "GamedevUltimate.h"
#include "Components/ArrowComponent.h"
#include "Engine/World.h"


AFirstSpawnActor::AFirstSpawnActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(RootComponent);
}

void AFirstSpawnActor::BeginPlay()
{
	Super::BeginPlay();

	const FVector Location =  ArrowComponent->GetComponentLocation();
	const FRotator Rotation = ArrowComponent->GetComponentRotation();
	FActorSpawnParameters Parameters = FActorSpawnParameters();
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	const AActor* Actor = GetWorld()->SpawnActor(ActorToSpawn, &Location, &Rotation, Parameters);
	if (bDebug && Actor) UE_LOG(LogGamedevUltimate, Log, TEXT("AFirstSpawnActor: Actor Spawned: %s at: %s"), *Actor->GetName(), *Location.ToString());
	if (Actor == nullptr) UE_LOG(LogGamedevUltimate, Warning, TEXT("AFirstSpawnActor: Actor Spawn failed!"))
}

void AFirstSpawnActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

