// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MultiAxisRotationActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API AMultiAxisRotationActor : public AActor
{
	GENERATED_BODY()

public:
	AMultiAxisRotationActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float YawRotationSpeed{100.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float PitchRotationSpeed{100.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float RollRotationSpeed{100.f};
};
