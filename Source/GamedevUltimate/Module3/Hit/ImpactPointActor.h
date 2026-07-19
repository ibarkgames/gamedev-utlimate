// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImpactPointActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API AImpactPointActor : public AActor
{
	GENERATED_BODY()

public:
	AImpactPointActor();

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ImpactPointActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ImpactPointActor, meta = (AllowPrivateAccess=true))
	bool bDebug{false};
};
