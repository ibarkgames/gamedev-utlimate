// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutomaticDoorActor.generated.h"

class UCurveFloat;
class UBoxComponent;

UENUM()
enum class EDoorState : uint8
{
	Idle,
	Elevating,
	Descending
};

UCLASS()
class GAMEDEVULTIMATE_API AAutomaticDoorActor : public AActor
{
	GENERATED_BODY()

public:
	AAutomaticDoorActor();

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
	
	void CalculateNextDoorLocation(const float DeltaTime, FVector& NewLocation, const FVector& TargetLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> DoorFrameMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> DoorMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	TArray<TObjectPtr<AActor>> OverlappingActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	float DoorTravellingDistance{250.f};
	
	FVector ClosedLocation{FVector::ZeroVector};
	
	FVector OpenLocation{FVector::ZeroVector};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	EDoorState DoorState{EDoorState::Idle};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UCurveFloat> SpeedCurve;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	float SpeedCurveLength{0.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	float Time{0.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	bool bDebug{false};
};
