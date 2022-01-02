// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "BruteAICharacter.generated.h"

class USpotLightComponent;

UCLASS()
class SURVIVALLAND_API ABruteAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABruteAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, Category = "AI")
	FLinearColor NoDetectionColor;

	UPROPERTY(EditAnywhere, Category = "AI")
	FLinearColor SeekingDetectionColor;

	UPROPERTY(EditAnywhere, Category = "AI")
	FLinearColor DetectionColor;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float WalkSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RunSpeed = 400.f;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TArray<ATargetPoint*> Waypoints;

	int CurrentWaypoint = 0;

	UPROPERTY(EditAnywhere, Category = "AI")
	float StartPos = 400.f;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float Length = 1500.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float Radius = 400.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float Height = 100.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float SecondsStopSeeingPlayer = 5.f;

	UFUNCTION()
	void DetectPlayerToPunch();

	UPROPERTY(EditAnywhere, Category = "AI")
	float StartPosPunch = 75.f;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float LengthPunch = 75.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	FVector BoxSize = FVector(15.f,75.f,75.f);

	UFUNCTION(BlueprintCallable, Category = "AI")
	bool GetPlayerDetected() { return PlayerDetected; }

	UPROPERTY(EditAnywhere, Category = "AI")
	UAnimMontage* PushMontage;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RadiusHear = 50.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float LenghtHear = 10.f;

	UFUNCTION(BlueprintNativeEvent, Category = "AI")
	void SetRightHandSphereActive(bool Value);
	
	UFUNCTION()
	void BeingWarned(FVector PlayerPos);

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

private:

	FTimerHandle TimerHandle;
	
	UPROPERTY()
	bool PlayerDetected = false;

	UFUNCTION()
	void StopPushAnim();


};
