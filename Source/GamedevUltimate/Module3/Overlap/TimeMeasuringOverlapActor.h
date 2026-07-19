// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeMeasuringOverlapActor.generated.h"

class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API ATimeMeasuringOverlapActor : public AActor
{
	GENERATED_BODY()

public:
	ATimeMeasuringOverlapActor();

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
	
	UFUNCTION()
	void OnComponentEndOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=TimeMeasuringOverlapActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> CollisionBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=TimeMeasuringOverlapActor, meta=(AllowPrivateAccess=true))
	TMap<FString, float> OverlappingActorTimes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=HitActor, meta = (AllowPrivateAccess=true))
	bool bDebug{false};
};
