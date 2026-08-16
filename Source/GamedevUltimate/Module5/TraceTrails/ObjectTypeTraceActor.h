// Copyright iBarkGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectTypeTraceActor.generated.h"

// Goal: Learn how to perform a line trace using object types instead of trace channels.
// You can perform a line trace using object types like "WorldStatic", instead of using trace channels like
// "Visibility". For this purpose there are alternative functions: LineTraceSingleByObjectType and
// LineTraceMultiByObjectType. Create an Actor that moves continuously in a straight line. Perform a line trace forwards
// from the Actors location, using the object type trace function. If the trace hits a WorldStatic Actor stop the
// movement. Place multiple walls in front of the Actor. Set some of the walls to be WorldStatic, and others
// WorldDynamic. Test and see how the Actor behaves.

class UTextRenderComponent;
UCLASS()
class GAMEDEVULTIMATE_API AObjectTypeTraceActor : public AActor
{
	GENERATED_BODY()

public:
	AObjectTypeTraceActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ObjectTypeTraceActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ObjectTypeTraceActor, meta = (AllowPrivateAccess = true))
	float Speed{ 100.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ObjectTypeTraceActor, meta = (AllowPrivateAccess = true))
	float TraceDistance{ 100.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ObjectTypeTraceActor, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRenderComponent;
};
