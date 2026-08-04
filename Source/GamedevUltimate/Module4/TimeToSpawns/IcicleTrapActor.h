// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IcicleTrapActor.generated.h"

class AIcicleSpikeActor;
class UBoxComponent;
UCLASS()
class GAMEDEVULTIMATE_API AIcicleTrapActor : public AActor
{
	GENERATED_BODY()

public:
	AIcicleTrapActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Schedule();

	UFUNCTION()
	void HandleSpawnedActorDestroyed(AActor* DestroyedActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IcicleTrapActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IcicleTrapActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IcicleTrapActor, meta = (AllowPrivateAccess = true))
	TSubclassOf<AIcicleSpikeActor> IcicleSpikeClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = IcicleTrapActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<AIcicleSpikeActor> SpawnedActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = IcicleTrapActor, meta = (AllowPrivateAccess = true))
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IcicleTrapActor, meta = (AllowPrivateAccess = true))
	FVector SpawnOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IcicleTrapActor, meta = (AllowPrivateAccess = true))
	FRotator SpawnRotatorOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IcicleTrapActor, meta = (AllowPrivateAccess = true))
	float SpawnDelay { 5.f };
	
	bool bIsSpawnScheduled { false };
};
