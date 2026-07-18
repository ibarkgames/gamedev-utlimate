// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongScaleActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API APingPongScaleActor : public AActor
{
	GENERATED_BODY()

public:
	APingPongScaleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	FVector UniformScale(float DeltaTime);
	
	FVector NonUniformScale(float DeltaTime);
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	float DefaultUniformScale;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	float UniformMaxScale{3.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	bool bUniformScale{true};
	
	bool bIsReturning{false};
	
	FVector DefaultNonUniformScale;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	FVector NonUniformMaxScale{3.f, 2.5f, 2.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	float ScalingSpeed{1.f};
};
