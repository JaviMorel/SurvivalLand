// Fill out your copyright notice in the Description page of Project Settings.


#include "BruteUpdateWaypointBTTaskNode.h"
#include "BruteAIController.h"

EBTNodeResult::Type UBruteUpdateWaypointBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABruteAIController* BruteAIController = Cast<ABruteAIController>(OwnerComp.GetOwner());

	BruteAIController->UpdateNextWaypoint();

	return EBTNodeResult::Succeeded;
}

FString UBruteUpdateWaypointBTTaskNode::GetStaticDescription() const
{
	return TEXT("Update the next waypoint of the AI");
}