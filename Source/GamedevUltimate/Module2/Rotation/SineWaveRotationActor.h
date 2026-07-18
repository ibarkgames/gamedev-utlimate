// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SineWaveRotationActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ASineWaveRotationActor : public AActor
{
	GENERATED_BODY()

public:
	ASineWaveRotationActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	FRotator Start;
	
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	FRotator End;
	
	float Time{0.f};
};
