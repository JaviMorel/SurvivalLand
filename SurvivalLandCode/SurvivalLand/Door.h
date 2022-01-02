// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Door.generated.h"

UCLASS()
class SURVIVALLAND_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Door")
	bool IsClosed = true;

	UFUNCTION(BlueprintCallable, Category = "Door")
	bool GetIsClosed(){ return IsClosed; }
	
	UPROPERTY(EditAnywhere, Category = "Door")
	int NumKeys = 0;

	int CurrentKeys = 0;

	UPROPERTY(EditAnywhere, Category = "Door")
	FVector EndOffset;

	UFUNCTION(BlueprintCallable, Category = "Door")
	void AddKey();
	
	UFUNCTION(BlueprintCallable, Category = "Door")
	void OpenDoor();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void CloseDoor();

	UTimelineComponent* TimeLine;
	
	/** Declare our delegate function to be binded with TimelineFloatReturn*/
	FOnTimelineFloat InterpFunction{};

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FcurveDoor;
	
	UFUNCTION()
	void TimelineFloatReturn(float const Value);

	FVector InitialPos;
	FVector EndPos;

	UPROPERTY(EditAnywhere)
	USoundBase* DoorOpenSound;
	

};
