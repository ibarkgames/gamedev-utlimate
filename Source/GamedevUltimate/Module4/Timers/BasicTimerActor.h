// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicTimerActor.generated.h"

class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API ABasicTimerActor : public AActor
{
	GENERATED_BODY()

public:
	ABasicTimerActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BasicTimerActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BasicTimerActor, meta = (AllowPrivateAccess = true))
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BasicTimerActor, meta = (AllowPrivateAccess = true))
	bool bDebug{ false };
};
