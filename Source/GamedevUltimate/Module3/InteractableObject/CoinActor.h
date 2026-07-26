// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ACoinActor : public AActor
{
	GENERATED_BODY()

public:
	ACoinActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex,
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CoinActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CoinActor, meta=(AllowPrivateAccess=true))
	FTimerHandle TimerHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CoinActor, meta=(AllowPrivateAccess=true))
	bool bCollected{false};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CoinActor, meta=(AllowPrivateAccess=true))
	float ShrinkingSpeed{5.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CoinActor, meta=(AllowPrivateAccess=true))
	float Time{0.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CoinActor, meta=(AllowPrivateAccess=true))
	float RotationSpeed{100.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CoinActor, meta = (AllowPrivateAccess=true))
	bool bDebug{false};
};
