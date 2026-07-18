// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineBasedMovementActor.generated.h"

class USplineComponent;

UCLASS()
class GAMEDEVULTIMATE_API ASplineBasedMovementActor : public AActor
{
	GENERATED_BODY()

public:
	ASplineBasedMovementActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	TSoftObjectPtr<AActor> SplineActor;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float Speed{100.f};
	
	UPROPERTY(VisibleAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USplineComponent> SplineComponent;
	
	float SplineLength{0.f};
	
	float Distance{0.f};
};
