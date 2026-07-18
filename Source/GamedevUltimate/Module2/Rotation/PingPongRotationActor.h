// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongRotationActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API APingPongRotationActor : public AActor
{
	GENERATED_BODY()

public:
	APingPongRotationActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float YawRotationSpeed{100.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float MaxYawRotation{360.f};
	
	bool bIsReturning{false};
};
