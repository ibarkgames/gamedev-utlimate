// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZoneActor.generated.h"

class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API AKillZoneActor : public AActor
{
	GENERATED_BODY()

public:
	AKillZoneActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=KillZoneActo, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=KillZoneActo, meta=(AllowPrivateAccess=true))
	FVector SpawnLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=KillZoneActo, meta=(AllowPrivateAccess=true))
	bool bDebug{false};
};
