// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurveScaleActor.generated.h"

class UCurveFloat;

UCLASS()
class GAMEDEVULTIMATE_API ACurveScaleActor : public AActor
{
	GENERATED_BODY()

public:
	ACurveScaleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	float TimeInCurve{0.f};

	UPROPERTY(EditAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCurveFloat> SpeedCurve;
	
	FVector DefaultScale;
	
	UPROPERTY(EditAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	FVector MaxScale;
	
	bool bIsReturning;
};
