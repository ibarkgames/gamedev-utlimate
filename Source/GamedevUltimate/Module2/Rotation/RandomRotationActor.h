// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomRotationActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ARandomRotationActor : public AActor
{
	GENERATED_BODY()

public:
	ARandomRotationActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float YawRotationSpeed{100.f};
	
	bool bIsYawRotationEnabled{false};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float PitchRotationSpeed{100.f};
	
	bool bIsPitchRotationEnabled{false};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float RollRotationSpeed{100.f};
	
	bool bIsRollRotationEnabled{false};
	
	float AccumulatedYaw = 0.f;
	float AccumulatedPitch = 0.f;
	float AccumulatedRoll = 0.f;
};
