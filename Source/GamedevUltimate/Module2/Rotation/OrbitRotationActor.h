// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrbitRotationActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API AOrbitRotationActor : public AActor
{
	GENERATED_BODY()

public:
	AOrbitRotationActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float RotationSpeed{100.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	float RotationRadius{300.f};
};
