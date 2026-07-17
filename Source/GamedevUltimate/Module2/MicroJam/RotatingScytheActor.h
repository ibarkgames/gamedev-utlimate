// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingScytheActor.generated.h"

class UCurveFloat;

UENUM()
enum class ETrapState : uint8
{
	Idle,
	Elevating,
	Moving,
	Descending
};

UCLASS()
class GAMEDEVULTIMATE_API ARotatingScytheActor : public AActor
{
	GENERATED_BODY()

public:
	ARotatingScytheActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	void Elevate(const float DeltaTime);
	
	void Descend(const float DeltaTime);
	
	void Move(const float DeltaTime);
	
	float CalculateDistanceToTarget() const;
	
	UPROPERTY(EditDefaultsOnly, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> BeamMesh;
	
	UPROPERTY(EditDefaultsOnly, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> AdaptorMesh;
	
	UPROPERTY(VisibleAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	ETrapState CurrentState{ETrapState::Idle};
	
	UPROPERTY(EditAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	TSoftObjectPtr<AActor> TargetActor;
	
	UPROPERTY(VisibleAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	FVector Start;
	
	UPROPERTY(EditAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	FVector End;
	
	UPROPERTY(VisibleAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	FVector BeamInitialLocation;
	
	UPROPERTY(EditAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	float ActivationDistance{1000.f};
	
	UPROPERTY(EditAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	float ElevationSpeed{50.f};
	
	UPROPERTY(EditAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	float MovingElevation{100.f};
	
	bool bIsReturning{false};
	
	UPROPERTY(EditAnywhere, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveFloat> SpeedCurve;
	
	UPROPERTY(EditAnywhere, Category = MovingObstacleActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveFloat> RotationSpeedCurve;
	
	UPROPERTY(VisibleAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	float Speed{100.f};
	
	UPROPERTY(VisibleAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	float RotationSpeed{50.f};
	
	UPROPERTY(VisibleAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	float Time{0.f};
	
		
	UPROPERTY(VisibleAnywhere, Category=RotatingScytheActor, meta=(AllowPrivateAccess=true))
	float RotationTime{0.f};
};
