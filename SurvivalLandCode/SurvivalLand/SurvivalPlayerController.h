// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalPlayerController.generated.h"

class ASurvivalLandCharacter;
class ACheckpoint;
/**
 * 
 */
UCLASS()
class SURVIVALLAND_API ASurvivalPlayerController : public APlayerController
{
	GENERATED_BODY()
		

private:
	UPROPERTY()
	TArray<ACheckpoint*> Checkpoints;

	UPROPERTY()
	int NextCheckpointID = 0;
	
	UPROPERTY()
	ACheckpoint* LastCheckpoint = nullptr;

	UFUNCTION()
	void SetActiveCurrentCheckpoint();
	
public:

	virtual void BeginPlay() override;
	
	//-------TUTORIAL-----------
	
	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void SetCanJump(bool NewValue);

	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void SetTutorialMode();
	
	//--------------------------

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void UpdateCurrentCheckpoint(int IDCheckpoint);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void SetPlayerToCheckpoint();

	UFUNCTION(BlueprintNativeEvent, Category = "Survival")
	void SetDeadPlayer();
	
	
};
