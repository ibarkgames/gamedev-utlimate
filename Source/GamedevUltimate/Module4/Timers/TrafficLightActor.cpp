// Copyright iBarkGames

#include "TrafficLightActor.h"

#include "Components/TextRenderComponent.h"

ATrafficLightActor::ATrafficLightActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
	TextComponent->SetupAttachment(RootComponent);
}
void ATrafficLightActor::BeginPlay()
{
	Super::BeginPlay();

	if (UMaterialInterface* ParentMaterial = Mesh ? Mesh->GetMaterial(0) : nullptr)
	{
		Material = UMaterialInstanceDynamic::Create(ParentMaterial, this);
		if (Material)
		{
			Mesh->SetMaterial(0, Material);
			SetColor();
		}
	}
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrafficLightActor::SwitchState, RedWaitingTime, false);
}

void ATrafficLightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const float Time = GetWorldTimerManager().GetTimerElapsed(TimerHandle);
	
	TextComponent->SetText(FText::AsNumber(Time));
}

void ATrafficLightActor::SwitchState()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	
	float NextWaitingTime = 0.f;
	
	switch (State)
	{
		case ETrafficLightState::Red:
			State = ETrafficLightState::Yellow;
			NextWaitingTime = YellowWaitingTime;
			break;
		case ETrafficLightState::Yellow:
			State = ETrafficLightState::Green;
			NextWaitingTime = GreenWaitingTime;
			break;
		case ETrafficLightState::Green:
			State = ETrafficLightState::Red;
			NextWaitingTime = RedWaitingTime;
			break;
	}

	SetColor();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrafficLightActor::SwitchState, NextWaitingTime, false);
}

void ATrafficLightActor::SetColor() const
{
	if (!Material)
	{
		return;
	}

	FColor Color = FColor::White;
	switch (State)
	{
		case ETrafficLightState::Red:
			Color = FColor::Red;
			break;
		case ETrafficLightState::Yellow:
			Color = FColor::Yellow;
			break;
		case ETrafficLightState::Green:
			Color = FColor::Green;
			break;
	}
	Material->SetVectorParameterValue("BaseColor", Color);
}
