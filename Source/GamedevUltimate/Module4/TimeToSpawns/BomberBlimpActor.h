// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BomberBlimpActor.generated.h"

class USplineComponent;
class ACannonProjectileActor;
class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API ABomberBlimpActor : public AActor
{
	GENERATED_BODY()

public:
	ABomberBlimpActor();

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<AActor> SplineActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	float Speed{100.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<USplineComponent> SplineComponent;
	
	float SplineLength{0.f};
	
	float Distance{0.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	TSubclassOf<ACannonProjectileActor> SpawnedActorClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<ACannonProjectileActor> SpawnedActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	FVector SpawnOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	FRotator SpawnRotatorOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	float SpawnDelay{ 3.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BomberBlimpActor, meta = (AllowPrivateAccess = true))
	float SpawnedActorLifeSpawn { 5.f };

	bool bIsSpawnScheduled{ false };
};
