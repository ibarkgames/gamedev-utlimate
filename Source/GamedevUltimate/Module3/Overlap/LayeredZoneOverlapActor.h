// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LayeredZoneOverlapActor.generated.h"

class USphereComponent;

UCLASS()
class GAMEDEVULTIMATE_API ALayeredZoneOverlapActor : public AActor
{
	GENERATED_BODY()

public:
	ALayeredZoneOverlapActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnComponentBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=LayeredZoneOverlapActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<USphereComponent> InnerSphere;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=LayeredZoneOverlapActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<USphereComponent> OuterSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=HitActor, meta = (AllowPrivateAccess=true))
	bool bDebug{false};
};
