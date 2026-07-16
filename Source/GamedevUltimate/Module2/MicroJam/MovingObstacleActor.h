// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObstacleActor.generated.h"

class UCurveFloat;

UCLASS()
class GAMEDEVULTIMATE_API AMovingObstacleActor : public AActor
{
	GENERATED_BODY()

public:
	AMovingObstacleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	FVector CalculateBasicMovement(const float DeltaTime);
	
	UPROPERTY(EditDefaultsOnly, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> OuterCircle;
	
	UPROPERTY(EditDefaultsOnly, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> InnerCircle;
	
	UPROPERTY(EditDefaultsOnly, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Arrows;
	
	UPROPERTY(EditAnywhere, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	TArray<AActor*> Targets;
	
	UPROPERTY(VisibleAnywhere, Category= MovingObstacleActor, meta = (AllowPrivateAccess = true))
	int NextTargetIndex{1};
	
	UPROPERTY(VisibleAnywhere, Category= MovingObstacleActor, meta = (AllowPrivateAccess = true))
	FTimerHandle TimerHandle;
	
	UPROPERTY(EditAnywhere, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	float WaitingTimeOnTarget{2.0f};
	
	UPROPERTY(VisibleAnywhere, Category= MovingObstacleActor, meta = (AllowPrivateAccess = true))
	bool bWaiting{false};
	
	UPROPERTY(EditAnywhere, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveFloat> SpeedCurve;
	
	UPROPERTY(VisibleAnywhere, Category= MovingObstacleActor, meta = (AllowPrivateAccess = true))
	float Time{0.f};
	
	UPROPERTY(EditAnywhere, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	float VerticalOscillation{10.f};
	
	UPROPERTY(EditAnywhere, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	float OscillationAmplitude{10.f};
	
	UPROPERTY(EditAnywhere, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	float RotationSpeed{100.f};
	
	UPROPERTY(EditAnywhere, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	float MinScale{0.1f};
	
	UPROPERTY(EditAnywhere, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	float MaxScale{1.0f};
	
	FVector BaseArrowsScale;
};
