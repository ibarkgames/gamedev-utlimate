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
}

void AGamedevUltimateCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
		                                   &AGamedevUltimateCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
		                                   &AGamedevUltimateCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::LookInput);

		// Module 1 test
		EnhancedInputComponent->BindAction(TriggerStatesAction, ETriggerEvent::Started, this,
		                                   &AGamedevUltimateCharacter::StartTriggerStatesInput);
		EnhancedInputComponent->BindAction(TriggerStatesAction, ETriggerEvent::Completed, this,
		                                   &AGamedevUltimateCharacter::CompleteTriggerStatesInput);
		EnhancedInputComponent->BindAction(TriggerStatesAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::TriggerTriggerStatesInput);
		EnhancedInputComponent->BindAction(TriggerStatesAction, ETriggerEvent::Ongoing, this,
		                                   &AGamedevUltimateCharacter::GoTriggerStatesInput);
		EnhancedInputComponent->BindAction(TriggerStatesAction, ETriggerEvent::Canceled, this,
		                                   &AGamedevUltimateCharacter::CancelTriggerStatesInput);

		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::Rotate);

		EnhancedInputComponent->BindAction(TestInputActionInstanceAction, ETriggerEvent::Ongoing, this,
		                                   &AGamedevUltimateCharacter::TestInputActionInstance);
		EnhancedInputComponent->BindAction(TestInputActionInstanceAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::TestInputActionInstance);

		EnhancedInputComponent->BindAction(TestTriggerQualifiersAction, ETriggerEvent::Triggered, this,
		                                   &AGamedevUltimateCharacter::TestTriggerQualifiers);
	}
	else
	{
		UE_LOG(LogGamedevUltimate, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}


void AGamedevUltimateCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AGamedevUltimateCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);
}

void AGamedevUltimateCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AGamedevUltimateCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AGamedevUltimateCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void AGamedevUltimateCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void AGamedevUltimateCharacter::StartTriggerStatesInput(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			1,
			2.0f,
			FColor::Green,
			TEXT("TriggerStatesAction Started!")
		);
	}
}

void AGamedevUltimateCharacter::CompleteTriggerStatesInput(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			2,
			2.0f,
			FColor::Green,
			TEXT("TriggerStatesAction Completed!")
		);
	}
}

void AGamedevUltimateCharacter::TriggerTriggerStatesInput(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			3,
			2.0f,
			FColor::Green,
			FString::Printf(TEXT("Triggered %f"), Instance.GetElapsedTime())
		);
	}
}

void AGamedevUltimateCharacter::GoTriggerStatesInput(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			4,
			2.0f,
			FColor::Green,
			FString::Printf(TEXT("OnGoing %f"), Instance.GetElapsedTime())
		);
	}
}

void AGamedevUltimateCharacter::CancelTriggerStatesInput(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			5,
			2.0f,
			FColor::Green,
			TEXT("TriggerStatesAction Cancelled!")
		);
	}
}

void AGamedevUltimateCharacter::Rotate(const FInputActionValue& Value)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Value.Get<float>());
	}
}

void AGamedevUltimateCharacter::TestInputActionInstance(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			6,
			2.0f,
			FColor::Green,
			FString::Printf(TEXT("Triggered: %f"), Instance.GetTriggeredTime())
		);
		GEngine->AddOnScreenDebugMessage(
			7,
			2.0f,
			FColor::Green,
			FString::Printf(TEXT("ElapsedTime: %f"), Instance.GetElapsedTime())
		);
		GEngine->AddOnScreenDebugMessage(
			8,
			2.0f,
			FColor::Green,
			FString::Printf(TEXT("Value %f"), Instance.GetValue().Get<float>())
		);
	}
}

void AGamedevUltimateCharacter::TestTriggerQualifiers(const FInputActionInstance& Instance)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			9,
			2.0f,
			FColor::Green,
			FString::Printf(TEXT("Triggered: %f"), Instance.GetTriggeredTime())
		);
	}
}
