// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamedevUltimateCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GamedevUltimate.h"
#include "Engine/Engine.h"

AGamedevUltimateCharacter::AGamedevUltimateCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f),
	                                                           FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->JumpZVelocity = DefaultJumpZVelocity;

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->NavAgentProps.bCanFly = true;
}

void AGamedevUltimateCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::DoJumpStart);
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
		//                                    &AGamedevUltimateCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::LookInput);

		// Module 1
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Started, this,
		                                   &AGamedevUltimateCharacter::DoWalk);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Completed, this,
		                                   &AGamedevUltimateCharacter::DoWalk);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Canceled, this,
		                                   &AGamedevUltimateCharacter::DoWalk);

		EnhancedInputComponent->BindAction(Gu_SprintAction, ETriggerEvent::Started, this,
		                                   &AGamedevUltimateCharacter::DoSprint);
		EnhancedInputComponent->BindAction(Gu_SprintAction, ETriggerEvent::Completed, this,
		                                   &AGamedevUltimateCharacter::DoSprint);
		EnhancedInputComponent->BindAction(Gu_SprintAction, ETriggerEvent::Canceled, this,
		                                   &AGamedevUltimateCharacter::DoSprint);

		EnhancedInputComponent->BindAction(ChargedJumpAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::DoChargedJumpStart);
		EnhancedInputComponent->BindAction(ChargedJumpAction, ETriggerEvent::Ongoing, this,
		                                   &AGamedevUltimateCharacter::DoChargedJumpStart);
		EnhancedInputComponent->BindAction(ChargedJumpAction, ETriggerEvent::Completed, this,
		                                   &AGamedevUltimateCharacter::DoChargedJumpEnd);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::DoCrouch);

		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::DoDash);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Ongoing, this,
		                                   &AGamedevUltimateCharacter::DoDash);

		EnhancedInputComponent->BindAction(SwitchFlyingAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::SwitchFlying);
		EnhancedInputComponent->BindAction(AscendAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::Ascending);
	}
	else
	{
		UE_LOG(LogGamedevUltimate, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void AGamedevUltimateCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultJumpZVelocity = GetCharacterMovement()->JumpZVelocity;
	DefaultCameraHeight = GetFirstPersonCameraComponent()->GetRelativeLocation().X;
	TargetCameraHeight = DefaultCameraHeight;
}

void AGamedevUltimateCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (
		float CameraHeight = GetFirstPersonCameraComponent()->GetRelativeLocation().X;
		!FMath::IsNearlyZero(CameraHeight - TargetCameraHeight, 0.01f)
	)
	{
		CameraHeight = FMath::FInterpTo(CameraHeight, TargetCameraHeight, DeltaTime, CameraInterpolationSpeed);
		FVector CameraLocation = GetFirstPersonCameraComponent()->GetRelativeLocation();
		CameraLocation.X = CameraHeight;
		GetFirstPersonCameraComponent()->SetRelativeLocation(CameraLocation);
	}
	if (StaminaRechargeDelay > 0.f)
	{
		StaminaRechargeDelay = FMath::Clamp(StaminaRechargeDelay - DeltaTime, 0.f, MaxStaminaRechargeDelay);
	}
	
	if (CurrentStamina < MaxStamina && !bIsSprinting && StaminaRechargeDelay == 0.f)
	{
		CurrentStamina += DeltaTime * StaminaRechargeRate;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0, MaxStamina);
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(15, 2.0f, FColor::Green,
			                                FString::Printf(TEXT("Current Stamina: %f"), CurrentStamina));
		}
#endif
	}
}

void AGamedevUltimateCharacter::OnStartCrouch(const float HalfHeightAdjust, const float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	TargetCameraHeight -= CameraCrouchOffset;
}

void AGamedevUltimateCharacter::OnEndCrouch(const float HalfHeightAdjust, const float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	TargetCameraHeight = DefaultCameraHeight;
}

void AGamedevUltimateCharacter::MoveInput(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (GetMovementComponent()->IsFlying())
	{
		DoFly(MovementVector.X, MovementVector.Y);
	}
	else
	{
		DoMove(MovementVector.X, MovementVector.Y);
	}
}

void AGamedevUltimateCharacter::LookInput(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoAim(LookAxisVector.X, LookAxisVector.Y);
}

void AGamedevUltimateCharacter::DoAim(const float Yaw, const float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AGamedevUltimateCharacter::DoMove(const float Right, const float Forward)
{
	if (GetController())
	{
		if (bIsSprinting && CurrentStamina > SprintStaminaConsumption)
		{
			ConsumeStamina(SprintStaminaConsumption);
		}
		else if (bIsSprinting)
		{
			ConsumeStamina(SprintStaminaConsumption);
			StopSprint();
		}
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AGamedevUltimateCharacter::DoFly(const float Right, const float Forward)
{
	if (GetController())
	{
		AddMovementInput(GetFirstPersonCameraComponent()->GetRightVector(), Right);
		AddMovementInput(GetFirstPersonCameraComponent()->GetForwardVector(), Forward);
	}
}

void AGamedevUltimateCharacter::DoJumpStart()
{
	
	if (CurrentStamina >= JumpStaminaConsumption)
	{
		ConsumeStamina(JumpStaminaConsumption);
		Jump();
	}
}

void AGamedevUltimateCharacter::DoJumpEnd()
{
	StopJumping();
}

void AGamedevUltimateCharacter::DoWalk(const FInputActionInstance& Instance)
{
	if (Instance.GetTriggerEvent() == ETriggerEvent::Started)
	{
		if (GetCharacterMovement()->IsFalling() || GetCharacterMovement()->IsCrouching())
		{
			return;
		}
		bIsWalking = true;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}
	else
	{
		bIsWalking = false;
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void AGamedevUltimateCharacter::DoSprint(const FInputActionInstance& Instance)
{
	if (Instance.GetTriggerEvent() == ETriggerEvent::Started)
	{
		if (GetCharacterMovement()->IsFalling() || GetCharacterMovement()->IsCrouching())
		{
			return;
		}
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else
	{
		StopSprint();
	}
}

void AGamedevUltimateCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
}

void AGamedevUltimateCharacter::DoChargedJumpStart(const FInputActionInstance& Instance)
{
	if (Instance.GetTriggerEvent() == ETriggerEvent::Ongoing)
	{
		if (GEngine)
		{
			const UInputTriggerHoldAndRelease* Trigger = static_cast<UInputTriggerHoldAndRelease*>(Instance.
				GetTriggers()[0]);
			const FString Message = Trigger->HoldTimeThreshold > Instance.GetElapsedTime()
				                        ? FString::Printf(TEXT("Jump is charging: %f"), Instance.GetElapsedTime())
				                        : TEXT("Ready to Jump");
			GEngine->AddOnScreenDebugMessage(11, 2.0f, FColor::Green, Message);
		}
		return;
	}
	
	if (!bIsChargedJumping && CurrentStamina > ChargedJumpStaminaConsumption)
	{
		ConsumeStamina(ChargedJumpStaminaConsumption);
		bIsChargedJumping = true;
		GetCharacterMovement()->JumpZVelocity = ChargedJumpZVelocity;
		Jump();
	}
}

void AGamedevUltimateCharacter::DoChargedJumpEnd(const FInputActionInstance& Instance)
{
	if (bIsChargedJumping)
	{
		GetCharacterMovement()->JumpZVelocity = DefaultJumpZVelocity;
		bIsChargedJumping = false;
	}
	StopJumping();
}

void AGamedevUltimateCharacter::DoCrouch(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		if (GetCharacterMovement()->IsFalling() || bIsSprinting)
		{
			return;
		}
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AGamedevUltimateCharacter::DoDash(const FInputActionInstance& Instance)
{
	if (bIsCrouched || CurrentStamina < DashStaminaConsumption)
	{
		return;
	}
	if (Instance.GetTriggerEvent() == ETriggerEvent::Ongoing)
	{
		if (GEngine)
		{
			const UInputTriggerHoldAndRelease* Trigger = static_cast<UInputTriggerHoldAndRelease*>(Instance.
				GetTriggers()[0]);
			const FString Message = Trigger->HoldTimeThreshold > Instance.GetElapsedTime()
				                        ? FString::Printf(TEXT("Dash is charging: %f"), Instance.GetElapsedTime())
				                        : TEXT("Ready to Dash");
			GEngine->AddOnScreenDebugMessage(13, 2.0f, FColor::Green, Message);
		}
		return;
	}
	ConsumeStamina(DashStaminaConsumption);
	FVector DashVector = GetActorForwardVector() * DashDirectionalVelocity;
	DashVector.Z += DashElevationVelocity;
	LaunchCharacter(DashVector, true, true);
}

void AGamedevUltimateCharacter::SwitchFlying(const FInputActionValue& Value)
{
	if (GetCharacterMovement()->IsFlying())
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else
	{
		if (GetCharacterMovement()->IsFalling() || bIsChargedJumping)
		{
			return;
		}

		GetCharacterMovement()->SetMovementMode(MOVE_Flying);

		FVector FlyLaunchVector = GetActorForwardVector();
		FlyLaunchVector.Z += FlyStartElevationVelocity;
		GetCharacterMovement()->Velocity = FlyLaunchVector;
	}
}

void AGamedevUltimateCharacter::Ascending(const FInputActionValue& Value)
{
	if (GetCharacterMovement()->IsFlying())
	{
		AddMovementInput(GetActorUpVector(), Value.Get<float>());
	}
}

void AGamedevUltimateCharacter::ConsumeStamina(const float Consumption)
{
	CurrentStamina -= Consumption;
	StaminaRechargeDelay = MaxStaminaRechargeDelay;
	CurrentStamina = FMath::Clamp(CurrentStamina, 0.f, MaxStamina);
}
