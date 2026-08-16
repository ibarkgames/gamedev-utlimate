// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StopHittingYourselfActor.generated.h"

class UTextRenderComponent;
UCLASS()
class GAMEDEVULTIMATE_API AStopHittingYourselfActor : public AActor
{
	GENERATED_BODY()

public:
	AStopHittingYourselfActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StopHittingYourselfActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StopHittingYourselfActor, meta = (AllowPrivateAccess = true))
	float TraceDistance{ 1000.f };

	UPROPERTY(
		VisibleAnywhere, BlueprintReadOnly, Category = StopHittingYourselfActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;
};
