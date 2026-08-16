// Copyright iBarkGames

#include "SweepVsTraceActor.h"

ASweepVsTraceActor::ASweepVsTraceActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASweepVsTraceActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASweepVsTraceActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Start = GetActorLocation();
	const FVector End = Start + GetActorForwardVector() * TraceLength;

	FHitResult TraceHitResult;
	FHitResult SweepHitResult;
	FColor TraceColor{ FColor::Red };
	const FColor SweepColor{ FColor::Yellow };

	GetWorld()->LineTraceSingleByChannel(TraceHitResult, Start, End, ECC_Visibility);
	GetWorld()->SweepSingleByChannel(
		SweepHitResult, Start, End, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(SweepRadius));
	if (TraceHitResult.bBlockingHit)
	{
		TraceColor = FColor::Green;
	}
	DrawDebugSphere(GetWorld(), Start, SweepRadius, 16, SweepColor);
	DrawDebugSphere(GetWorld(), End, SweepRadius, 16, SweepColor);
	if (SweepHitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), SweepHitResult.Location, SweepRadius, 16, SweepColor);
	}
	DrawDebugLine(GetWorld(), Start, End, TraceColor, false, 0.f, 0, 1.f);
}
