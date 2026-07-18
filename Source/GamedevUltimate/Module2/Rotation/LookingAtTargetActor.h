// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LookingAtTargetActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ALookingAtTargetActor : public AActor
{
	GENERATED_BODY()

public:
	ALookingAtTargetActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	TSoftObjectPtr<AActor> TargetActor;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float RotationSpeed{5.f};
};
