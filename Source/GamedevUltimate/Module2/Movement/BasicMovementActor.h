// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicMovementActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ABasicMovementActor : public AActor
{
	GENERATED_BODY()

public:
	ABasicMovementActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta = (AllowPrivateAccess = "true"))
	FVector MovingDirection = FVector(0.0f, 0.0f, 1.0f);
	
	UPROPERTY(EditAnywhere, Category="Components", meta = (AllowPrivateAccess = "true"))
	float MovingSpeed{100.f};
};
