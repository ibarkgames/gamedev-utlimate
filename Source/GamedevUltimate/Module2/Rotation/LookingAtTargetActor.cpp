// Copyright iBarkGames


#include "LookingAtTargetActor.h"

#include "GamedevUltimatePlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ALookingAtTargetActor::ALookingAtTargetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ALookingAtTargetActor::BeginPlay()
{
	Super::BeginPlay();
	
	const APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (APawn* PlayerPawn = PC ? PC->GetPawn() : nullptr)
	{
		TargetActor = Cast<AActor>(PlayerPawn);
	}
}

void ALookingAtTargetActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!TargetActor.IsValid()) return;
	
	const FQuat Quat = GetActorQuat();
	const FQuat TargetQuat = 
		UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation()).Quaternion();
	const FQuat NewQuat = FMath::QInterpTo(Quat, TargetQuat, DeltaTime, RotationSpeed).GetNormalized();
	
	SetActorRotation(NewQuat);
}

