// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomizeScaleActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ARandomizeScaleActor : public AActor
{
	GENERATED_BODY()

public:
	ARandomizeScaleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	void SetTargetScales();
	
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	FVector MinScales{0.1f, 0.1f, 0.1f};
	
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	FVector MaxScales{2.5f, 2.5f, 2.5f};
	
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	FVector TargetScales{};
	
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	float ScalingSpeed{100.f};
	
	UPROPERTY(VisibleAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	FTimerHandle TimerHandle;
};
