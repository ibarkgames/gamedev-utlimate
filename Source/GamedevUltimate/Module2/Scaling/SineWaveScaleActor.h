// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SineWaveScaleActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ASineWaveScaleActor : public AActor
{
	GENERATED_BODY()

public:
	ASineWaveScaleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	FVector MinScale{0.f, 0.f, 0.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	FVector MaxScale{1.0f, 1.5f, 0.5f};
	
	float Time{0.f};
};
