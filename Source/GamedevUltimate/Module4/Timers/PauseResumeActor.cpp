// Copyright iBarkGames

#include "PauseResumeActor.h"

#include "Components/BoxComponent.h"
#include "Components/TextBlock.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"

APauseResumeActor::APauseResumeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);

	Text = CreateDefaultSubobject<UTextRenderComponent>("Text");
	Text->SetupAttachment(RootComponent);
}

void APauseResumeActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APauseResumeActor::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APauseResumeActor::OnEndOverlap);

	GetWorldTimerManager().SetTimer(
		TimerHandle,
		[this] {

		},
		TimerInterval, true);
}

void APauseResumeActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDebug)
		GEngine->AddOnScreenDebugMessage(50, 0.5f, FColor::Green,
			FString::Printf(TEXT("APauseResumeActor: %f"), GetWorldTimerManager().GetTimerElapsed(TimerHandle)));

	Text->SetText(FText::FromString(
		FString::Printf(TEXT("Elapsed time: %f"), GetWorldTimerManager().GetTimerElapsed(TimerHandle))));
}

void APauseResumeActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const ACharacter* Character = Cast<ACharacter>(OtherActor); Character)
	{
		GetWorldTimerManager().PauseTimer(TimerHandle);
	}
}

void APauseResumeActor::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (const ACharacter* Character = Cast<ACharacter>(OtherActor); Character)
	{
		GetWorldTimerManager().UnPauseTimer(TimerHandle);
	}
}
