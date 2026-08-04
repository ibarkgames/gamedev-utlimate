// Copyright iBarkGames

#include "WaveSpawnerActor.h"

#include "GamedevUltimate.h"
#include "Chaos/Deformable/MuscleActivationConstraints.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

AWaveSpawnerActor::AWaveSpawnerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void AWaveSpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWaveSpawnerActor::OnBeginOverlap);
}

// Called every frame
void AWaveSpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AWaveSpawnerActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const ACharacter* Character = Cast<ACharacter>(OtherActor); Character && &bWavesStarted)
	{
		CurrentWave = 0;
		bWavesStarted = true;
		ScheduleNextWave();
	}
	else if (bDebug)
	{
		UE_LOG(LogGamedevUltimate, Log, TEXT("AWaveSpawnerActor: %i wave is going, cannot restart before finish"),
			CurrentWave);
	}
}

void AWaveSpawnerActor::ScheduleNextWave()
{
	if (WaveSpawnerActorData.Num() < CurrentWave)
	{
		return;
	}

	if (CurrentWave == WaveSpawnerActorData.Num())
	{
		bWavesStarted = false;
		return;
	}

	if (bDebug)
		UE_LOG(LogGamedevUltimate, Log, TEXT("AWaveSpawnerActor: Spawning %i wave"), CurrentWave);

	const FWaveData& Data = WaveSpawnerActorData[CurrentWave];
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		[this, Data] {
			SpawnNextWave(Data);
			CurrentWave += 1;
			ScheduleNextWave();
		},
		Data.Delay, false);
}

void AWaveSpawnerActor::SpawnNextWave(const FWaveData& Data)
{
	if (bDebug)
		UE_LOG(LogGamedevUltimate, Log, TEXT("AWaveSpawnerActor: SpawnNextWave: %s"), *Data.ActorClassToSpawn->GetName());
	
	FVector				  SpawnLocation = GetActorLocation();
	const FRotator		  SpawnRotation = GetActorRotation();
	FActorSpawnParameters Parameters = FActorSpawnParameters();
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	for (int32 i = 0; i < Data.AmountToSpawn; i++)
	{
		SpawnLocation.X += Data.PositionOffset;
		AActor* Actor = GetWorld()->SpawnActor(Data.ActorClassToSpawn, &SpawnLocation, &SpawnRotation, Parameters);
		Actor->SetLifeSpan(Data.LifeSpanSeconds);
	}
}
