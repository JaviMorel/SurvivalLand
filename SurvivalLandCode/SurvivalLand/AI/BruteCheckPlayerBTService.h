// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BruteCheckPlayerBTService.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALLAND_API UBruteCheckPlayerBTService : public UBTService
{
	GENERATED_BODY()

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
