// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "CountdownBombActor.generated.h"

class UBoxComponent;
class UNiagaraSystem;
UCLASS()
class GAMEDEVULTIMATE_API ACountdownBombActor : public AActor
{
	GENERATED_BODY()

public:
	ACountdownBombActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Explode();

	void ApplyForce();

	UFUNCTION()
	void OnExplosionFinished(UNiagaraComponent* FinishedComponent);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	FTimerHandle ExplodeTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	float ExplodeDelay{ 5.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	bool bArmed{ false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	float ExplosionRadius{ 300.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	float ExplosionForce{ 1000.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	float ExplosionVelocityToCharacter{ 100.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	TEnumAsByte<ECollisionChannel> ExplosionChannel{ ECC_WorldDynamic };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	bool bDebug{ false };
};
