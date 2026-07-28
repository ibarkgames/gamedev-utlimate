// Copyright iBarkGames

#include "LoopingTimerActor.h"

#include "Dataflow/DataflowDebugDraw.h"

ALoopingTimerActor::ALoopingTimerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneComponent);
}

void ALoopingTimerActor::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(Mesh.Get()->GetMaterial(0), this);
	Mesh->SetMaterial(0, Material);

	if (Colors.Num() > 1)
	{
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			[this, Material]() {
				SetRandomColorIndex();
				Material->SetVectorParameterValue("BaseColor", Colors[ColorIndex]);
			},
			LoopTime, true);
	}
}

// Called every frame
void ALoopingTimerActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALoopingTimerActor::SetRandomColorIndex()
{
	if (Colors.Num() < 2)
	{
		return;
	}

	int NextIndex = FMath::RandRange(0, Colors.Num() - 1);
	while (NextIndex == ColorIndex)
	{
		NextIndex = FMath::RandRange(0, Colors.Num() - 1);
	}
	ColorIndex = NextIndex;
}
