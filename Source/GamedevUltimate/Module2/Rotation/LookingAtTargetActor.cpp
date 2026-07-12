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
	const double X = FMath::FInterpTo(Quat.X, TargetQuat.X, DeltaTime, RotationSpeed);
	const double Y = FMath::FInterpTo(Quat.Y, TargetQuat.Y, DeltaTime, RotationSpeed);
	const double Z = FMath::FInterpTo(Quat.Z, TargetQuat.Z, DeltaTime, RotationSpeed);
	const double W = FMath::FInterpTo(Quat.W, TargetQuat.W, DeltaTime, RotationSpeed);
	
	SetActorRotation(FQuat{X, Y, Z, W});
}

