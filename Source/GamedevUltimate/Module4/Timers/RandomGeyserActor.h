// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomGeyserActor.generated.h"

class UTextRenderComponent;
class UNiagaraSystem;
class UBoxComponent;
UCLASS()
class GAMEDEVULTIMATE_API ARandomGeyserActor : public AActor
{
	GENERATED_BODY()

public:
	ARandomGeyserActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void Explode();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	FTimerHandle ExplodeTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	FVector BoxSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	float MinExplodeDelay{ 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	float MaxExplodeDelay{ 10.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	bool bArmed{ false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	TEnumAsByte<ECollisionChannel> ExplosionChannel{ ECC_WorldDynamic };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	float MinExplosionForce{ 100.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	float MaxExplosionForce{ 1000.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	float CharacterExplosionCoefficient{ 0.1f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CountdownBombActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> ExplosionSound;
};
