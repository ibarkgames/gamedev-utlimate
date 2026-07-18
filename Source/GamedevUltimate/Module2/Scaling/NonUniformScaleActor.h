// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NonUniformScaleActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ANonUniformScaleActor : public AActor
{
	GENERATED_BODY()

public:
	ANonUniformScaleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	FVector MaxScale{2.0f, 2.5f, 3.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	FVector ScaleSpeed{1.5f, 1.2f, 1.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	bool bUseInterpolation{false};
};
