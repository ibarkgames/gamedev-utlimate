// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedCurvesActor.generated.h"

class UCurveFloat;

UCLASS()
class GAMEDEVULTIMATE_API ASpeedCurvesActor : public AActor
{
	GENERATED_BODY()

public:
	ASpeedCurvesActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	FVector Start;

	UPROPERTY(EditAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	FVector End;

	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	bool bIsReturning;

	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	float TimeInCurve{0.f};

	UPROPERTY(EditAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCurveFloat> SpeedCurve;
};
