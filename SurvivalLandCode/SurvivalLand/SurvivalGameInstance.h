// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SurvivalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALLAND_API USurvivalGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	const FString SaveSlot = "SurvivalLand";
	UPROPERTY()
	int CurrentLevel = 0;

	UFUNCTION(BlueprintCallable, Category = "Level")
	int GetCurrentLevel() { return CurrentLevel; }

	UFUNCTION(BlueprintCallable, Category = "Level")
	void SetCurrentLevel(int level) { CurrentLevel = level; }
	
	UPROPERTY()
	int CheckpointID = -1;

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	int GetCheckpointID() { return CheckpointID; }

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void SetCheckpointID(int ID) { CheckpointID = ID; }
		
	UFUNCTION(BlueprintCallable, Category = "Survival Save Game")
	void SaveGameToSlot();

	UFUNCTION(BlueprintCallable, Category = "Survival Save Game")
	void LoadGameToSlot();

	UFUNCTION(BlueprintCallable, Category = "Survival Save Game")
	void DeleteGameToSlot();
	
};
