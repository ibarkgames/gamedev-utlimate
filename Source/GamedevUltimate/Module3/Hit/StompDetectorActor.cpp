// Copyright iBarkGames


#include "StompDetectorActor.h"

#include "GamedevUltimate.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"


AStompDetectorActor::AStompDetectorActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void AStompDetectorActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &AStompDetectorActor::OnHit);
	
	Colors.Add(FColor::Red);
	Colors.Add(FColor::Green);
	Colors.Add(FColor::Blue);
	Colors.Add(FColor::Yellow);
	Colors.Add(FColor::Cyan);
	
	Material = UMaterialInstanceDynamic::Create(Mesh.Get()->GetMaterial(0), this);
	Mesh->SetMaterial(0, Material);
}

void AStompDetectorActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStompDetectorActor::OnHit(
	UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, 
	const FHitResult& Hit
)
{
	if (OtherActor && OtherActor != this && Colors.Num() >= 1)
	{
		if (
			FMath::Abs(Hit.ImpactNormal.X) <= HorizontalImpactThreshold &&
			FMath::Abs(Hit.ImpactNormal.Y) <= HorizontalImpactThreshold &&
			FMath::Abs(Hit.ImpactNormal.Z) >= VerticalImpactThreshold
		)
		{
			if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("STOMPED"));
			ColorIndex = (ColorIndex + 1) % Colors.Num(); 
			Material->SetVectorParameterValue("BaseColor", Colors[ColorIndex]);
		}
	}
}

