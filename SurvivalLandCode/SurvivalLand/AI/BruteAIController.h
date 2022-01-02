// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BruteAIController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALLAND_API ABruteAIController : public AAIController
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "AIBrute")
	void CheckPlayer();

	UFUNCTION(BlueprintCallable, Category = "AIBrute")
	void SetNextWaypoint();

	UFUNCTION(BlueprintCallable, Category = "AIBrute")
	void UpdateNextWaypoint();

	UFUNCTION(BlueprintCallable, Category = "AIBrute")
	void MoveToPlayer();
	
	UFUNCTION(BlueprintCallable, Category = "AIBrute")
	void ReachLastLocationOfPlayer();

	AActor* Player;

	bool PlayerSeen = false;
	
	float SecondsLeftSeeingPlayer = 0.f;

	UFUNCTION()
	void PlayerDetectedByInformer(FVector InformerLastPosPlayer);

};
