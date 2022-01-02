// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "InformerAICharacter.generated.h"

class USpotLightComponent;
class UAudioComponent;

UCLASS()
class SURVIVALLAND_API AInformerAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInformerAICharacter();

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

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float WalkSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RunSpeed = 800.f;
	
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

	UPROPERTY(EditAnywhere, Category = "AI")
	float UnitsFleeToPlayer = -1000.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RandomRadiusFleeToPlayer = 500.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RadiusWarnBrutes = 400.f;

	UFUNCTION()
	void SetWarning(bool Value) { Warning = Value; }

private:
	UPROPERTY()
	bool Warning = false;

	UFUNCTION()
	void Shouting();
};
