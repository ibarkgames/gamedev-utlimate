// Copyright iBarkGames

#include "CannonProjectileActor.h"

#include "GamedevUltimate.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ACannonProjectileActor::ACannonProjectileActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->SetSimulatePhysics(true);
}

void ACannonProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &ACannonProjectileActor::OnHit);
}

void ACannonProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACannonProjectileActor::Launch(const FVector& Velocity)
{
	if (Mesh->IsSimulatingPhysics())
	{
		Mesh->SetPhysicsLinearVelocity(Velocity);
	}
}
bool ACannonProjectileActor::IsPhysicsEnabled() const
{
	return Mesh->IsSimulatingPhysics();
}

void ACannonProjectileActor::SetSimulatePhysics(const bool bEnabled)
{
	Mesh->SetSimulatePhysics(bEnabled);
}

void ACannonProjectileActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bHasExploded)
		return;
	if (OtherActor == this || OtherActor == GetOwner())
		return;

	bHasExploded = true;
	Explode();

	if (!ExplosionEffect)
	{
		UE_LOG(LogGamedevUltimate, Warning, TEXT("ACannonProjectileActor: No ExplosionEffect has been set!"));
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
		SpawnedEffect->OnSystemFinished.AddDynamic(this, &ACannonProjectileActor::OnExplosionFinished);
	}
}

void ACannonProjectileActor::Explode()
{
	TArray<FOverlapResult> Overlaps;
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(ExplosionRadius);
	GetWorld()->OverlapMultiByChannel(Overlaps, GetActorLocation(), FQuat::Identity, ExplosionChannel, Sphere);

	for (FOverlapResult& Overlap : Overlaps)
	{
		if (AActor* Actor = Overlap.GetActor(); Actor)
		{
			if (ACharacter* Character = Cast<ACharacter>(Actor); Character)
			{
				UE_LOG(LogGamedevUltimate, Log, TEXT("ACannonProjectileActor: Character overlapping %s"),
					*Character->GetName());
				FVector Direction = Character->GetActorLocation() - GetActorLocation();
				Direction.Normalize();
				Direction *= ExplosionCharacterLaunch;
				Character->LaunchCharacter(Direction, true, true);
			}
			else
			{
				UE_LOG(
					LogGamedevUltimate, Log, TEXT("ACannonProjectileActor: Actor overlapping %s"), *Actor->GetName());
				Overlap.GetComponent()->AddRadialImpulse(
					GetActorLocation(), ExplosionRadius, ExplosionForce, RIF_Linear, false);
			}

			Mesh->SetVisibility(false);
			Mesh->SetSimulatePhysics(false);
			Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void ACannonProjectileActor::OnExplosionFinished(UNiagaraComponent* FinishedComponent)
{
	Destroy();
}
