// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableDoorActor.generated.h"

UCLASS()
class GAMEDEVULTIMATE_API ABreakableDoorActor : public AActor
{
	GENERATED_BODY()

public:
	ABreakableDoorActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, 
		const FHitResult& Hit 
	);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=BreakableDoorActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> DoorFrameMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=BreakableDoorActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> DoorMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=BreakableDoorActor, meta=(AllowPrivateAccess=true))
	float MinimumVelocity{400.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=BreakableDoorActor, meta=(AllowPrivateAccess=true))
	float ImpulseScale{0.1f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=BreakableDoorActor, meta=(AllowPrivateAccess=true))
	bool bDebug{false};
};
