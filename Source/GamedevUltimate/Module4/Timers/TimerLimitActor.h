// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerLimitActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ATimerLimitActor : public AActor
{
	GENERATED_BODY()

public:
	ATimerLimitActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TimerLimitActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TimerLimitActor, meta = (AllowPrivateAccess = true))
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TimerLimitActor, meta = (AllowPrivateAccess = true))
	float LoopTime{ 3.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TimerLimitActor, meta = (AllowPrivateAccess = true))
	int LoopCounter{ 0 };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TimerLimitActor, meta = (AllowPrivateAccess = true))
	int LoopCounterLimit{ 5 };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TimerLimitActor, meta = (AllowPrivateAccess = true))
	float MinElevation{20.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TimerLimitActor, meta = (AllowPrivateAccess = true))
	float MaxElevation{100.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TimerLimitActor, meta = (AllowPrivateAccess = true))
	bool bDebug{ false };
};
