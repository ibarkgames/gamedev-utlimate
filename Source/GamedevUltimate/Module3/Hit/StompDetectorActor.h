// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StompDetectorActor.generated.h"

class UMaterialInstanceDynamic;

UCLASS()
class GAMEDEVULTIMATE_API AStompDetectorActor : public AActor
{
	GENERATED_BODY()

public:
	AStompDetectorActor();

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=StompDetectorActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StompDetectorActor, meta = (AllowPrivateAccess=true))
	float HorizontalImpactThreshold{0.1f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StompDetectorActor, meta = (AllowPrivateAccess=true))
	float VerticalImpactThreshold{0.98f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=StompDetectorActor, meta = (AllowPrivateAccess=true))
	TArray<FColor> Colors;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=StompDetectorActor, meta = (AllowPrivateAccess=true))
	int ColorIndex{0};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StompDetectorActor, meta = (AllowPrivateAccess=true))
	bool bDebug{false};
	
	TObjectPtr<UMaterialInstanceDynamic> Material;
};
