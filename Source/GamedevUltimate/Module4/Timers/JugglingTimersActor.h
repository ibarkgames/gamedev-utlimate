// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JugglingTimersActor.generated.h"

class UTextRenderComponent;
UCLASS()
class GAMEDEVULTIMATE_API AJugglingTimersActor : public AActor
{
	GENERATED_BODY()

public:
	AJugglingTimersActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	FTimerHandle MaterialTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	float MaterialTimerInterval{ 1.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	TArray<FColor> Colors;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	int ColorIndex{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	FTimerHandle LogTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	float LogTimerInterval{ 3.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> ActorClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	float SpawnTimerInterval{ 5.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	FVector SpawnLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	FRotator SpawnRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JugglingTimersActor, meta = (AllowPrivateAccess = true))
	bool bDebug{ false };
};
