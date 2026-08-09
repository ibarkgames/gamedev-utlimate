// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelectiveVisionActor.generated.h"

class UTextRenderComponent;
UCLASS()
class GAMEDEVULTIMATE_API ASelectiveVisionActor : public AActor
{
	GENERATED_BODY()

public:
	ASelectiveVisionActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SelectiveVisionActor, meta = (AllowPrivateAccess = true))
	float TraceDistance{ 1000.f };

	UPROPERTY(
		VisibleAnywhere, BlueprintReadOnly, Category = SelectiveVisionActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;
};
