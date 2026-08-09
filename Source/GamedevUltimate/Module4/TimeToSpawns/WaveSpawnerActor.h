// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveSpawnerActor.generated.h"

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ActorClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 AmountToSpawn{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Delay{ 3.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LifeSpanSeconds{ 5.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PositionOffset{ 200.f };
};

class UBoxComponent;
UCLASS()
class GAMEDEVULTIMATE_API AWaveSpawnerActor : public AActor
{
	GENERATED_BODY()

public:
	AWaveSpawnerActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ScheduleNextWave();

	UFUNCTION()
	void SpawnNextWave(const FWaveData& Data);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WaveSpawnerActor, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WaveSpawnerActor, meta = (AllowPrivateAccess = "true"))
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WaveSpawnerActor, meta = (AllowPrivateAccess = "true"))
	TArray<FWaveData> WaveSpawnerActorData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WaveSpawnerActor, meta = (AllowPrivateAccess = "true"))
	int32 CurrentWave{ 0 };
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WaveSpawnerActor, meta = (AllowPrivateAccess = "true"))
	bool bWavesStarted{ false };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WaveSpawnerActor, meta = (AllowPrivateAccess = true))
	bool bDebug{ false };
};
