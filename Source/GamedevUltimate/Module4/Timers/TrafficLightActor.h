// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficLightActor.generated.h"

class UTextRenderComponent;
UENUM()
enum class ETrafficLightState : uint8
{
	Red,
	Yellow,
	Green
};

UCLASS()
class GAMEDEVULTIMATE_API ATrafficLightActor : public AActor
{
	GENERATED_BODY()

public:
	ATrafficLightActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void SwitchState();
	
	void SetColor() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TrafficLightActor, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TrafficLightActor, meta=(AllowPrivateAccess = true))
	TObjectPtr<UMaterialInstanceDynamic> Material;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TrafficLightActor, meta=(AllowPrivateAccess = true))
	FTimerHandle TimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TrafficLightActor, meta=(AllowPrivateAccess = true))
	ETrafficLightState State {ETrafficLightState::Red};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TrafficLightActor, meta=(AllowPrivateAccess = true))
	float RedWaitingTime {5.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TrafficLightActor, meta=(AllowPrivateAccess = true))
	float YellowWaitingTime {2.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TrafficLightActor, meta=(AllowPrivateAccess = true))
	float GreenWaitingTime {4.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TrafficLightActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextComponent;
};
