// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SurvivalSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALLAND_API USurvivalSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int Level = 0;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	int GetLevel() { return Level; }

	UPROPERTY()
	int CheckpointID = -1;

	UFUNCTION(BlueprintCallable, Category = "Survival")
	int GetCheckpointID() { return CheckpointID; }

	UPROPERTY()
	bool IsArcadeAvailable = false;
	
	UFUNCTION(BlueprintCallable, Category = "Survival")
	bool GetIsArcadeAvailable() { return IsArcadeAvailable; }
	
	
};
