// Copyright iBarkGames

#include "CountdownBombActor.h"

#include "GamedevUltimate.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ACountdownBombActor::ACountdownBombActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);

	Text = CreateDefaultSubobject<UTextRenderComponent>("Text");
	Text->SetupAttachment(RootComponent);
}

void ACountdownBombActor::BeginPlay()
{
	Super::BeginPlay();
	Text->SetVisibility(false);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACountdownBombActor::OnBeginOverlap);
}

void ACountdownBombActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDebug && bArmed)
		GEngine->AddOnScreenDebugMessage(50, 0.5f, FColor::Red,
			FString::Printf(TEXT("ACountdownBombActor: Explode in: %f seconds"),
				ExplodeDelay - GetWorldTimerManager().GetTimerElapsed(ExplodeTimer)));

	if (bArmed)
		Text->SetText(FText::AsNumber(ExplodeDelay - GetWorldTimerManager().GetTimerElapsed(ExplodeTimer)));
}

void ACountdownBombActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const ACharacter* Character = Cast<ACharacter>(OtherActor); !bArmed && Character)
	{
		bArmed = true;
		Text->SetVisibility(true);
		GetWorldTimerManager().SetTimer(ExplodeTimer, this, &ACountdownBombActor::Explode, ExplodeDelay, false);
	}
}
void ACountdownBombActor::Explode()
{

	if (!ExplosionEffect)
	{
		UE_LOG(LogGamedevUltimate, Warning, TEXT("ACountdownBombActor: No ExplosionEffect has been set!"));
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
		SpawnedEffect->OnSystemFinished.AddDynamic(this, &ACountdownBombActor::OnExplosionFinished);
	}

	ApplyForce();
}

void ACountdownBombActor::ApplyForce()
{
	TArray<FOverlapResult> Overlaps;
	const FCollisionShape  Sphere = FCollisionShape::MakeSphere(ExplosionRadius);
	GetWorld()->OverlapMultiByChannel(Overlaps, GetActorLocation(), FQuat::Identity, ExplosionChannel, Sphere);

	for (FOverlapResult& Overlap : Overlaps)
	{
		if (AActor* Actor = Overlap.GetActor(); Actor)
		{
			if (ACharacter* Character = Cast<ACharacter>(Actor); Character)
			{
				UE_LOG(LogGamedevUltimate, Log, TEXT("ACountdownBombActor: Character overlapping %s"),
					*Character->GetName());
				FVector Direction = Character->GetActorLocation() - GetActorLocation();
				Direction.Normalize();
				Direction *= ExplosionVelocityToCharacter;
				Character->LaunchCharacter(Direction, true, true);
			}
			else
			{
				UE_LOG(LogGamedevUltimate, Log, TEXT("ACountdownBombActor: Actor overlapping %s"), *Actor->GetName());
				Overlap.GetComponent()->AddRadialImpulse(
					GetActorLocation(), ExplosionRadius, ExplosionForce, RIF_Linear, false);
			}
		}
	}
}

void ACountdownBombActor::OnExplosionFinished(UNiagaraComponent* FinishedComponent)
{
	Destroy();
}
