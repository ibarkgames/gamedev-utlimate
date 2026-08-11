// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RobotCleanerActor.generated.h"

class UArrowComponent;
UCLASS()
class GAMEDEVULTIMATE_API ARobotCleanerActor : public AActor
{
	GENERATED_BODY()

public:
	ARobotCleanerActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "RobotCleanerActor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "RobotCleanerActor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> ArrowComponent;

	UPROPERTY(EditAnywhere, Category = "RobotCleanerActor", meta = (AllowPrivateAccess = "true"))
	float Speed{ 100.f };

	UPROPERTY(EditAnywhere, Category = "RobotCleanerActor", meta = (AllowPrivateAccess = "true"))
	bool bSweep{ true };
};
