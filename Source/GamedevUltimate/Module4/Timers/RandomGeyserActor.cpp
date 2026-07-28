// Copyright iBarkGames

#include "RandomGeyserActor.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ARandomGeyserActor::ARandomGeyserActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void ARandomGeyserActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		ExplodeTimer, this, &ARandomGeyserActor::Explode, FMath::RandRange(MinExplodeDelay, MaxExplodeDelay), false);
}

void ARandomGeyserActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARandomGeyserActor::Explode()
{

	TArray<FOverlapResult> Overlaps;
	const FCollisionShape  Box = FCollisionShape::MakeBox(BoxSize);
	GetWorld()->OverlapMultiByChannel(Overlaps, GetActorLocation(), FQuat::Identity, ExplosionChannel, Box);

	const float ExplosionForce = FMath::RandRange(MinExplosionForce, MaxExplosionForce);

	for (FOverlapResult& Overlap : Overlaps)
	{
		if (AActor* Actor = Overlap.GetActor(); Actor && Actor != this)
		{
			if (ACharacter* Character = Cast<ACharacter>(Actor); Character)
			{
				FVector Direction = Character->GetActorUpVector();
				Direction.Normalize();
				// TODO: finetune
				Direction *= ExplosionForce;
				Character->LaunchCharacter(Direction, true, true);
			}
			else
			{
				if (UPrimitiveComponent* Component = Overlap.GetComponent();
					Component && Component->IsSimulatingPhysics())
				{
					FVector Direction = Component->GetComponentLocation();
					Direction.X = 0;
					Direction.Y = 0;
					Direction.Normalize();
					Direction *= ExplosionForce;
					Component->AddImpulseAtLocation(Direction, Component->GetComponentLocation(), FName());
				}
			}
		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(), ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator);

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	}

	GetWorldTimerManager().SetTimer(
		ExplodeTimer, this, &ARandomGeyserActor::Explode, FMath::RandRange(MinExplodeDelay, MaxExplodeDelay), false);
}
