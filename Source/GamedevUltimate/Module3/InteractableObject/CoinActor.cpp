// Copyright iBarkGames


#include "CoinActor.h"

#include "GamedevUltimate.h"
#include "GamedevUltimateCharacter.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"


ACoinActor::ACoinActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneComponent);
}

void ACoinActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ACoinActor::OnHit);
}

void ACoinActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bCollected)
	{
		Time += DeltaTime;
		FVector NextScale = GetActorScale3D();
		NextScale = FMath::VInterpConstantTo(NextScale, FVector::ZeroVector, DeltaTime, ShrinkingSpeed);
		SetActorScale3D(NextScale);
	}
	
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(NewRotation);
}

void ACoinActor::OnHit(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (!bCollected && OtherActor && OtherActor->IsA(AGamedevUltimateCharacter::StaticClass()))
	{
		if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("Coin collected!"));
		bCollected = true;
		GetWorldTimerManager().SetTimer(
				TimerHandle,
				[this]()
				{
					if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("Coin will be destroyed!"));
					Destroy();
				},
				5.f,
				false
			);
	}
}
