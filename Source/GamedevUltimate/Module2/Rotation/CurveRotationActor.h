// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurveRotationActor.generated.h"

class UCurveFloat;

UCLASS()
class GAMEDEVULTIMATE_API ACurveRotationActor : public AActor
{
	GENERATED_BODY()

public:
	ACurveRotationActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	float TimeInCurve{0.f};

	UPROPERTY(EditAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCurveFloat> SpeedCurve;
};
