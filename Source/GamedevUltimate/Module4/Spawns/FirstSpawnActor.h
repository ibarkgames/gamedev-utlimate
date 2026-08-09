// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstSpawnActor.generated.h"

class UArrowComponent;

UCLASS()
class GAMEDEVULTIMATE_API AFirstSpawnActor : public AActor
{
	GENERATED_BODY()

public:
	AFirstSpawnActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstSpawnActor, meta=(AllowPrivateAccess=true))
	TSubclassOf<AActor> ActorToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstSpawnActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UArrowComponent> ArrowComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstSpawnActor, meta =(AllowPrivateAccess=true))
	bool bDebug{false};
};
