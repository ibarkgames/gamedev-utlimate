// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UniformScaleActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API AUniformScaleActor : public AActor
{
	GENERATED_BODY()

public:
	AUniformScaleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	float ScaleSpeed{10.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	float MaxScale{3.f};
};
