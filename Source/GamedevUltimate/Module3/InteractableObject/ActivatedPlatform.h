// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActivatedPlatform.generated.h"

class UBoxComponent;

UCLASS()
class GAMEDEVULTIMATE_API AActivatedPlatform : public AActor
{
	GENERATED_BODY()

public:
	AActivatedPlatform();

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
	
	void MoveActor(const float DeltaTime, FVector& NewLocation, const FVector& TargetLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	FVector StartLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	FVector EndLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	float Speed{100};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	bool bActivated{false};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AutomaticDoorActor, meta=(AllowPrivateAccess=true))
	bool bReturning{false};
};
