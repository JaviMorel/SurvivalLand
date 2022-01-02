// Fill out your copyright notice in the Description page of Project Settings.


#include "InformerUpdateWaypointBTTaskNode.h"
#include "InformerAIController.h"

EBTNodeResult::Type UInformerUpdateWaypointBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AInformerAIController* InformerAIController = Cast<AInformerAIController>(OwnerComp.GetOwner());

	InformerAIController->UpdateNextWaypoint();

	return EBTNodeResult::Succeeded;
}

FString UInformerUpdateWaypointBTTaskNode::GetStaticDescription() const
{
	return TEXT("Update the next waypoint of the AI");
}
