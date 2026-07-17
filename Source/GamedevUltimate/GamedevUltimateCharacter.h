// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "GamedevUltimateCharacter.generated.h"

struct FInputActionInstance;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS(abstract)
class AGamedevUltimateCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MouseLookAction;
	
	/** Module 1 Movement Abilities */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* WalkAction;
	
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* Gu_SprintAction;
	
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* ChargedJumpAction;
	
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* CrouchAction;
	
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* DashAction;
	
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* SwitchFlyingAction;
	
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* AscendAction;
	
public:
	AGamedevUltimateCharacter();

protected:
	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoFly(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();
	
	void DoWalk(const FInputActionInstance& Instance);
	
	void DoSprint(const FInputActionInstance& Instance);
	
	void StopSprint();
	
	void DoChargedJumpStart(const FInputActionInstance& Instance);
	
	void DoChargedJumpEnd(const FInputActionInstance& Instance);
	
	void DoCrouch(const FInputActionValue& Value);
	
	void DoDash(const FInputActionInstance& Instance);
	
	void SwitchFlying(const FInputActionValue& Value);
	
	void Ascending(const FInputActionValue& Value);
	
	void ConsumeStamina(const float Consumption);
	
	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaTime ) override;
	
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	
public:
	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float WalkingSpeed{200.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	bool bIsWalking{false};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float RunningSpeed{400.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float SprintingSpeed{800.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float DefaultJumpZVelocity{420.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	bool bIsSprinting{false};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float ChargedJumpZVelocity{840.f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	bool bIsChargedJumping{false};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float DefaultCameraHeight{};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float TargetCameraHeight{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float CameraCrouchOffset{64.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float CameraInterpolationSpeed{8.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float DashDirectionalVelocity{1200.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float DashElevationVelocity{200.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float FlyStartElevationVelocity{50.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components|Stamina", meta = (AllowPrivateAccess = "true"))
	float MaxStamina{100.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components|Stamina", meta = (AllowPrivateAccess = "true"))
	float CurrentStamina{100.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components|Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaRechargeRate{10.0f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components|Stamina", meta = (AllowPrivateAccess = "true"))
	float MaxStaminaRechargeDelay{2.0f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components|Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaRechargeDelay{2.0f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float SprintStaminaConsumption{0.1f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float JumpStaminaConsumption{5.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float ChargedJumpStaminaConsumption{10.f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	float DashStaminaConsumption{10.f};
};
