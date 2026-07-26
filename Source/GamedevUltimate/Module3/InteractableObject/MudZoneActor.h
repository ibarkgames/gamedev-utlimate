// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MudZoneActor.generated.h"

class ACharacter;
class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API AMudZoneActor : public AActor
{
	GENERATED_BODY()

public:
	AMudZoneActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
	
	UFUNCTION()
	void OnEndOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MudZoneActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=MudZoneActor, meta=(AllowPrivateAccess=true))
	TArray<TObjectPtr<ACharacter>> OverlappingCharacters;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MudZoneActor, meta=(AllowPrivateAccess=true))
	float SlowingFactor{2.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MudZoneActor, meta=(AllowPrivateAccess=true))
	bool bDebug{false};
};
