// Copyright iBarkGames

#include "BasicTimerActor.h"

#include "GamedevUltimate.h"

ABasicTimerActor::ABasicTimerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneComponent);
}

void ABasicTimerActor::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(Mesh.Get()->GetMaterial(0), this);
	Mesh->SetMaterial(0, Material);
	Material->SetVectorParameterValue("BaseColor", FColor::Red);

	GetWorldTimerManager().SetTimer(
		TimerHandle,
		[this, Material]() {
			if (bDebug)
				UE_LOG(LogGamedevUltimate, Log, TEXT("ABasicTimerActor: Change color!"));
			Material->SetVectorParameterValue("BaseColor", FColor::Green);
		},
		3.f, false);
}

void ABasicTimerActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}
