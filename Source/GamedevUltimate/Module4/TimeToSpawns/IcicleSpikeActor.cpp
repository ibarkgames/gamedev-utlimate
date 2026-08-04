// Copyright iBarkGames

#include "IcicleSpikeActor.h"

#include "GamedevUltimate.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AIcicleSpikeActor::AIcicleSpikeActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Mesh->SetSimulatePhysics(false);
	Mesh->SetNotifyRigidBodyCollision(true);
}
void AIcicleSpikeActor::TurnPhysicsOn() const
{
	Mesh->SetSimulatePhysics(true);
}

void AIcicleSpikeActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &AIcicleSpikeActor::OnHit);
}

void AIcicleSpikeActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogGamedevUltimate, Warning, TEXT("Icicle hit: %s"), *GetNameSafe(OtherActor));
	if (!ExplosionEffect)
	{
		UE_LOG(LogGamedevUltimate, Warning, TEXT("AIcicleSpikeActor: No ExplosionEffect has been set!"));
		Destroy();
		return;
	}

	UNiagaraComponent* SpawnedEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(), ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator);

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	}

	if (SpawnedEffect)
	{
		SpawnedEffect->OnSystemFinished.AddDynamic(this, &AIcicleSpikeActor::OnExplosionFinished);
	}
}

void AIcicleSpikeActor::OnExplosionFinished(UNiagaraComponent* FinishedComponent)
{
	Destroy();
}

