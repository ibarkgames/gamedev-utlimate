// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CannonActor.generated.h"

class ACannonProjectileActor;
class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API ACannonActor : public AActor
{
	GENERATED_BODY()

public:
	ACannonActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SpawnProjectile();
	
	void Shoot(AActor* Actor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonActor, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonActor, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CannonActor, meta = (AllowPrivateAccess = "true"))
	FTimerHandle TimerHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CannonActor, meta = (AllowPrivateAccess = "true"))
	bool bScheduled { false };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonActor, meta = (AllowPrivateAccess = "true"))
	float Delay{ 3.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonActor, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACannonProjectileActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonActor, meta = (AllowPrivateAccess = "true"))
	float SpawnedActorLifeSpawn{ 10.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonActor, meta = (AllowPrivateAccess = "true"))
	float StartVelocity{ 1000.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonActor, meta = (AllowPrivateAccess = "true"))
	float ElevationAngle = 15.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonActor, meta = (AllowPrivateAccess = "true"))
	float SpawnOffset { 100.f };
};
