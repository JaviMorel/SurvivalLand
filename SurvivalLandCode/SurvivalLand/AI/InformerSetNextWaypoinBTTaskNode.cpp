// Fill out your copyright notice in the Description page of Project Settings.


#include "InformerSetNextWaypoinBTTaskNode.h"
#include "InformerAIController.h"

EBTNodeResult::Type UInformerSetNextWaypoinBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AInformerAIController* InformerAIController = Cast<AInformerAIController>(OwnerComp.GetOwner());

	InformerAIController->SetNextWaypoint();

	return EBTNodeResult::Succeeded;
}

FString UInformerSetNextWaypoinBTTaskNode::GetStaticDescription() const
{
	return TEXT("Set the current waypoint of the AI");
}
