// Copyright iBarkGames


#include "MudZoneActor.h"

#include "GamedevUltimate.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


AMudZoneActor::AMudZoneActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

void AMudZoneActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMudZoneActor::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AMudZoneActor::OnEndOverlap);
}

void AMudZoneActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMudZoneActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		if (!OverlappingCharacters.Contains(Character))
		{
			if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("OnBeginOverlap %s"), *Character->GetName());
			Character->GetCharacterMovement()->MaxWalkSpeed /= SlowingFactor;
			Character->GetCharacterMovement()->MaxWalkSpeedCrouched /= SlowingFactor;
			OverlappingCharacters.Add(Character);
		}
	}
}

void AMudZoneActor::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex
)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor); Character && OverlappingCharacters.Contains(Character))
	{
		if (bDebug) UE_LOG(LogGamedevUltimate, Log, TEXT("OnEndOverlap %s"), *Character->GetName());
		Character->GetCharacterMovement()->MaxWalkSpeed *= SlowingFactor;
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched *= SlowingFactor;
		OverlappingCharacters.Remove(Character);
	}
}
