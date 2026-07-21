// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlateActor.generated.h"

class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API APressurePlateActor : public AActor
{
	GENERATED_BODY()

public:
	APressurePlateActor();

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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PressurePlateActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PressurePlateActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=PressurePlateActor, meta=(AllowPrivateAccess=true))
	TArray<TObjectPtr<AActor>> Actors;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=PressurePlateActor, meta=(AllowPrivateAccess=true))
	float StartLocation{0.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=PressurePlateActor, meta=(AllowPrivateAccess=true))
	float EndLocation{0.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PressurePlateActor, meta=(AllowPrivateAccess=true))
	float TravelingDistance{20.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PressurePlateActor, meta=(AllowPrivateAccess=true))
	float TravelingSpeed{10.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MudZoneActor, meta=(AllowPrivateAccess=true))
	bool bDebug{false};
};
