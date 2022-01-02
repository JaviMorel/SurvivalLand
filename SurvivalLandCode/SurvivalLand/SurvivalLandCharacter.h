// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivalLandCharacter.generated.h"

UCLASS(config=Game)
class ASurvivalLandCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ASurvivalLandCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	virtual void Tick(float DeltaSeconds) override;
	
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void Run();
	void StopRunning();
	
	void StartJumping();
	void StopJumpingF();
	
	
	
	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, Category = "Player")
	float WalkSpeed = 350.f;

	UPROPERTY(EditAnywhere, Category = "Player")
	float RunSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Player")
	float SlipperyPlusSpeed = 100.f;
	
	UPROPERTY()
	bool IsRunning = false;

	UFUNCTION(BlueprintCallable)
	bool GetIsRunning() { return IsRunning; }
	
	UPROPERTY()
	bool IsJumping = false;

	UFUNCTION(BlueprintCallable)
	bool GetIsJumping() { return IsJumping; }

	UPROPERTY()
	bool IsSlippery = false;

	UFUNCTION(BlueprintCallable)
	bool GetIsSlippery() { return IsSlippery; }

	UFUNCTION(BlueprintCallable)
	void SetIsSlippery(bool NewValue) { IsSlippery = NewValue; }

	UPROPERTY()
	bool IsSpeedIncreased = false;

	UPROPERTY()
	float SpeedIncreasedPowerUp = 0.f;

	UFUNCTION(BlueprintCallable)
	bool GetIsSpeedIncreased() { return IsSpeedIncreased; }

	UFUNCTION(BlueprintCallable)
	void SetIsSpeedIncreased(bool NewValue, float SpeedPowerUp) { IsSpeedIncreased = NewValue; SpeedIncreasedPowerUp = SpeedPowerUp; }
	
	UPROPERTY()
	bool bCanRun = true;
	
	UPROPERTY()
	bool bCanJump = true;

	UPROPERTY(EditAnywhere, Category = "Player")
	float MaxHealth = 100.f;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	float GetMaxHealth() { return MaxHealth; }

	UPROPERTY(EditAnywhere, Category = "Player")
	float CurrentHealth = MaxHealth;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	float GetCurrentHealth() { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void RestoreHealth(float HealthRestored);

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void RestoreAllHealth() { CurrentHealth = MaxHealth; }
	
	UFUNCTION(BlueprintCallable, Category = "Survival")
	void ApplyDamageToPlayer(float Damage);

	UPROPERTY()
	bool IsDead = false;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void SetIsDead(bool NewValue) { IsDead = NewValue; }

	UPROPERTY()
	bool IsInvisible = false;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void SetIsInvisible(bool NewValue) { IsInvisible = NewValue; }

	UPROPERTY()
	bool IsShieldActivated = false;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	void SetIsShieldActivated(bool NewValue) { IsShieldActivated = NewValue; }
	
	UFUNCTION(BlueprintNativeEvent)
	void SetDamageImage();

	UPROPERTY(EditAnywhere)
	USoundBase* DeathSound;

};

