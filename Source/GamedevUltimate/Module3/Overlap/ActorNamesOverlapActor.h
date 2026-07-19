// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorNamesOverlapActor.generated.h"

class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API AActorNamesOverlapActor : public AActor
{
	GENERATED_BODY()

public:
	AActorNamesOverlapActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	void LogOverlappingActors() const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=AActorNamesOverlapActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AActorNamesOverlapActor, meta=(AllowPrivateAccess=true))
	FTimerHandle TimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=HitActor, meta = (AllowPrivateAccess=true))
	bool bDebug{false};
};
