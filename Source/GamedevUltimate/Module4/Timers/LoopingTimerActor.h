// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoopingTimerActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ALoopingTimerActor : public AActor
{
	GENERATED_BODY()

public:
	ALoopingTimerActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void SetRandomColorIndex();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LoopingTimerActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LoopingTimerActor, meta = (AllowPrivateAccess = true))
	TArray<FColor> Colors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LoopingTimerActor, meta = (AllowPrivateAccess = true))
	int ColorIndex{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LoopingTimerActor, meta = (AllowPrivateAccess = true))
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LoopingTimerActor, meta = (AllowPrivateAccess = true))
	float LoopTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LoopingTimerActor, meta = (AllowPrivateAccess = true))
	bool bDebug{ false };
};
