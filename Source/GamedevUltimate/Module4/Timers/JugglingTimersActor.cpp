// Copyright iBarkGames

#include "JugglingTimersActor.h"

#include "Components/TextRenderComponent.h"

AJugglingTimersActor::AJugglingTimersActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
	TextComponent->SetupAttachment(RootComponent);
}

void AJugglingTimersActor::BeginPlay()
{
	Super::BeginPlay();

	TextComponent->SetVisibility(false);

	UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(Mesh.Get()->GetMaterial(0), this);
	Mesh->SetMaterial(0, Material);
	
	GetWorldTimerManager().SetTimer(MaterialTimerHandle, [this, Material]() {
		Material->SetVectorParameterValue("BaseColor", Colors[ColorIndex]);
		ColorIndex = ColorIndex >= Colors.Num() - 1 ? 0 : ColorIndex + 1;
	}, MaterialTimerInterval, true);
	
	GetWorldTimerManager().SetTimer(
		LogTimerHandle, [this]() {
			TextComponent->SetVisibility(true);
			TextComponent->SetText(FText::AsNumber(GetWorld()->GetTimeSeconds()));
		}, LogTimerInterval, true);
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, [this]() {
		GetWorld()->SpawnActor(ActorClassToSpawn, &SpawnLocation, &SpawnRotation, FActorSpawnParameters());
	}, SpawnTimerInterval, true);
}

void AJugglingTimersActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
