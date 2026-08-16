// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RangeFinderActor.generated.h"

class UTextRenderComponent;
UCLASS()
class GAMEDEVULTIMATE_API ARangeFinderActor : public AActor
{
	GENERATED_BODY()

public:
	ARangeFinderActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RangeFinderActor, meta=(AllowPrivateAccess=true))
	float TraceDistance { 1000.f };
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RangeFinderActor, meta=(AllowPrivateAccess=true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RangeFinderActor, meta = (AllowPrivateAccess = true))
	bool bDebug{ false };
};
