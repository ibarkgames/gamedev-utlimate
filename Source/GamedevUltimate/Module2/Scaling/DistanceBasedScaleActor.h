// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DistanceBasedScaleActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ADistanceBasedScaleActor : public AActor
{
	GENERATED_BODY()

public:
	ADistanceBasedScaleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	FVector StartLocation;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	FVector EndLocation;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	float MovingSpeed{100.f};
	
	FVector StartScale;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	FVector MaxScale{2.0f, 2.0f, 2.0f};
	
	bool bIsReturning{false};
};
