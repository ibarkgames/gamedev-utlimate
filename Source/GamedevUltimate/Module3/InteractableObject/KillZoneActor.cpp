// Copyright iBarkGames


#include "KillZoneActor.h"

#include "GamedevUltimate.h"
#include "GamedevUltimateCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


AKillZoneActor::AKillZoneActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void AKillZoneActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AKillZoneActor::OnBeginOverlap);
	
	// APlayerStart
	if (const AActor* PlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()))
	{
		SpawnLocation = PlayerStart->GetActorLocation();
	}
}

void AKillZoneActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKillZoneActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (OtherActor && OtherActor->IsA(AGamedevUltimateCharacter::StaticClass()))
	{
		if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("Respawn!"));
		OtherActor->SetActorLocation(SpawnLocation);
	}
}

