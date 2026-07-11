// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FollowTheLeaderActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API AFollowTheLeaderActor : public AActor
{
	GENERATED_BODY()

public:
	AFollowTheLeaderActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Components", meta = (AllowPrivateAccess = "true"))
	float MovingSpeed{100.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta = (AllowPrivateAccess = "true"))
	float MinimumDistanceFromTarget{100.f};
	
	UPROPERTY(EditAnywhere, Category="Components", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<AActor> TargetActor;
};
