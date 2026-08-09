// Copyright iBarkGames

#include "SentryEyeActor.h"

#include "GamedevUltimate.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

ASentryEyeActor::ASentryEyeActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh1");
	Mesh->SetupAttachment(RootComponent);

	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh2");
	Mesh2->SetupAttachment(Mesh);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComponent->SetupAttachment(RootComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("Text");
	TextRenderComponent->SetupAttachment(RootComponent);
	TextRenderComponent->SetTextRenderColor(FColor::Red);
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TextRenderComponent->SetRelativeRotation(FRotator(0.0f, -45.0f, 0.0f));
	TextRenderComponent->SetText(FText::FromString("TraceRadarActor"));
}

void ASentryEyeActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASentryEyeActor::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ASentryEyeActor::OnEndOverlap);

	TextRenderComponent->SetVisibility(false);
	
	UMaterialInterface* ParentMaterial = Mesh ? Mesh->GetMaterial(0) : nullptr;
	if (!ParentMaterial)
	{
		UE_LOG(LogGamedevUltimate, Warning, TEXT("ASentryEyeActor::BeginPlay: ParentMaterial is null"));
		return;
	}

	if (UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(ParentMaterial, this))
	{
		MaterialInstance = Material;
		Mesh->SetMaterial(0, MaterialInstance);
		MaterialInstance->SetVectorParameterValue("BaseColor", FColor::White);
	}
}

void ASentryEyeActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TraceRadarCharacter != nullptr)
	{
		const FVector CharacterLocation = TraceRadarCharacter->GetActorLocation();

		const FQuat Quat = GetActorQuat();
		const FQuat TargetQuat =
			UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CharacterLocation).Quaternion();
		const FQuat NewQuat = FMath::QInterpTo(Quat, TargetQuat, DeltaTime, RotationSpeed).GetNormalized();
		SetActorRotation(NewQuat);

		FHitResult HitResult;
		const FVector StartLocation = Mesh2->GetComponentLocation();
		const FVector EndLocation = StartLocation + GetActorForwardVector() * TraceDistance;
		FCollisionObjectQueryParams CollisionObjectQueryParams;
		CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
		CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(this);
		GetWorld()->LineTraceSingleByObjectType(
			HitResult, StartLocation, EndLocation, CollisionObjectQueryParams, CollisionQueryParams);

		FColor LineColor = FColor::Green;
		if (HitResult.GetActor() == TraceRadarCharacter)
		{
			LineColor = FColor::Red;
			MaterialInstance->SetVectorParameterValue("BaseColor", FColor::Red);
		}
		else
		{
			MaterialInstance->SetVectorParameterValue("BaseColor", FColor::White);
		}
		if (HitResult.bBlockingHit)
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 15.f, 32, LineColor);
		}
		DrawDebugLine(GetWorld(), GetActorLocation(), CharacterLocation, LineColor);
	}
}

void ASentryEyeActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor); IsValid(Character))
	{
		TraceRadarCharacter = Character;
		TextRenderComponent->SetVisibility(true);
		TextRenderComponent->SetText(FText::FromString("Character detected: " + Character->GetName()));
		GetWorld()->GetTimerManager().SetTimer(
			WarningTimer, [this] { TextRenderComponent->SetVisibility(false); }, WarningMessageTime, false);
	}
}

void ASentryEyeActor::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (const ACharacter* Character = Cast<ACharacter>(OtherActor); IsValid(Character))
	{
		TraceRadarCharacter = nullptr;
		TextRenderComponent->SetVisibility(true);
		TextRenderComponent->SetText(FText::FromString("Character escaped: " + Character->GetName()));
		GetWorld()->GetTimerManager().SetTimer(
			WarningTimer, [this] { TextRenderComponent->SetVisibility(false); }, WarningMessageTime, false);
	}
}
