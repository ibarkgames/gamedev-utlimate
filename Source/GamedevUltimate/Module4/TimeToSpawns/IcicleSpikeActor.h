// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IcicleSpikeActor.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
UCLASS()
class GAMEDEVULTIMATE_API AIcicleSpikeActor : public AActor
{
	GENERATED_BODY()

public:
	AIcicleSpikeActor();
	
	void TurnPhysicsOn() const;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnExplosionFinished(UNiagaraComponent* FinishedComponent);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IcicleSpikeActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IcicleSpikeActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IcicleSpikeActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> ExplosionSound;
};
