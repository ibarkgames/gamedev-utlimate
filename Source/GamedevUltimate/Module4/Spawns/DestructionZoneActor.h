// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructionZoneActor.generated.h"

class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API ADestructionZoneActor : public AActor
{
	GENERATED_BODY()

public:
	ADestructionZoneActor();

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DestructionZoneActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DestructionZoneActor, meta=(AllowPrivateAccess=true))
	bool bDebug{false};
};
