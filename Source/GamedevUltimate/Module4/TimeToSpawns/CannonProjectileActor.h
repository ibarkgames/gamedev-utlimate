// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CannonProjectileActor.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class USphereComponent;
UCLASS()
class GAMEDEVULTIMATE_API ACannonProjectileActor : public AActor
{
	GENERATED_BODY()

public:
	ACannonProjectileActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	void Launch(const FVector& Velocity);
	
	bool IsPhysicsEnabled() const;
	
	void SetSimulatePhysics(bool bEnabled);

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void Explode();

	UFUNCTION()
	void OnExplosionFinished(UNiagaraComponent* FinishedComponent);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonProjectileActor, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonProjectileActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonProjectileActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonProjectileActor, meta = (AllowPrivateAccess = true))
	float ExplosionRadius{ 300.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonProjectileActor, meta = (AllowPrivateAccess = true))
	float ExplosionForce{ 1000.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonProjectileActor, meta = (AllowPrivateAccess = true))
	float ExplosionCharacterLaunch{ 100.f };
	
	bool bHasExploded = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CannonProjectileActor, meta = (AllowPrivateAccess = true))
	TEnumAsByte<ECollisionChannel> ExplosionChannel{ ECC_WorldDynamic };
};
