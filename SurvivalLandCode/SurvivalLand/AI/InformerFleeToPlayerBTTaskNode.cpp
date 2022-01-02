// Fill out your copyright notice in the Description page of Project Settings.


#include "InformerFleeToPlayerBTTaskNode.h"
#include "InformerAIController.h"

EBTNodeResult::Type UInformerFleeToPlayerBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AInformerAIController* InformerAIController = Cast<AInformerAIController>(OwnerComp.GetOwner());

	InformerAIController->FleeToPlayer();

	return EBTNodeResult::Succeeded;
}

FString UInformerFleeToPlayerBTTaskNode::GetStaticDescription() const
{
	return TEXT("Set the current waypoint of the AI");
}
