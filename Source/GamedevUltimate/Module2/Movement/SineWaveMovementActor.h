// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SineWaveMovementActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ASineWaveMovementActor : public AActor
{
	GENERATED_BODY()

public:
	ASineWaveMovementActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	FVector Start;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	FVector End;
	
	float Time;
};
