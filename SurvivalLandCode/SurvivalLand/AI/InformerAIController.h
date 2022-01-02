// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "InformerAIController.generated.h"

class AInformerAICharacter;
/**
 * 
 */
UCLASS()
class SURVIVALLAND_API AInformerAIController : public AAIController
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "AIInformer")
	void CheckPlayer();

	UFUNCTION(BlueprintCallable, Category = "AIInformer")
	void SetNextWaypoint();

	UFUNCTION(BlueprintCallable, Category = "AIInformer")
	void UpdateNextWaypoint();

	UFUNCTION(BlueprintCallable, Category = "AIInformer")
	void FleeToPlayer();

	UFUNCTION()
	void WarnBrutes(AInformerAICharacter* Informer);

	AActor* Player;

	bool PlayerSeen = false;

	float SecondsLeftSeeingPlayer = 0.f;

	FVector LastPlayerPos;

};
