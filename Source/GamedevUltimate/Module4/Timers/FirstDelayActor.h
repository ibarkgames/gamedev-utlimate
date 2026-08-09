// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstDelayActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API AFirstDelayActor : public AActor
{
	GENERATED_BODY()

public:
	AFirstDelayActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstDelayActor, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=FirstDelayActor, meta=(AllowPrivateAccess = true))
	FTimerHandle TimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstDelayActor, meta=(AllowPrivateAccess = true))
	float LoopTime{3.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstDelayActor, meta=(AllowPrivateAccess = true))
	float FirstDelay{1.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstDelayActor, meta=(AllowPrivateAccess = true))
	float MinRotation{1.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstDelayActor, meta=(AllowPrivateAccess = true))
	float MaxRotation{90.f};
};
