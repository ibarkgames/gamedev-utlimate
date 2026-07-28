// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PauseResumeActor.generated.h"

class UTextRenderComponent;
class UBoxComponent;
UCLASS()
class GAMEDEVULTIMATE_API APauseResumeActor : public AActor
{
	GENERATED_BODY()

public:
	APauseResumeActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PauseResumeActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PauseResumeActor, meta = (AllowPrivateAccess = true))
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PauseResumeActor, meta = (AllowPrivateAccess = true))
	float TimerInterval{ 0.1f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PauseResumeActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PauseResumeActor, meta = (AllowPrivateAccess = true))
	bool bDebug{ false };
};
