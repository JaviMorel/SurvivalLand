// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "InformerSetNextWaypoinBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALLAND_API UInformerSetNextWaypoinBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	virtual FString GetStaticDescription() const override;
	
};