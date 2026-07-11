// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DirectionalMovement.generated.h"

class UArrowComponent;

UCLASS()
class GAMEDEVULTIMATE_API ADirectionalMovement : public AActor
{
	GENERATED_BODY()

public:
	ADirectionalMovement();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> MovingDirection;
	
	UPROPERTY(EditAnywhere, Category="Components", meta = (AllowPrivateAccess = "true"))
	float MovingSpeed{100.f};
};
