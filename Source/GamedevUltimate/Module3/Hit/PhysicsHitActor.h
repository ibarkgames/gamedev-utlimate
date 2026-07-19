// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsHitActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API APhysicsHitActor : public AActor
{
	GENERATED_BODY()

public:
	APhysicsHitActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=PhysicsHitActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=PhysicsHitActor, meta = (AllowPrivateAccess=true))
	bool bDebug{false};
};
