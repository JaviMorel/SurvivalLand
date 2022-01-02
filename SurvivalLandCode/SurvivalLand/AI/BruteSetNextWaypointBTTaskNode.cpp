// Fill out your copyright notice in the Description page of Project Settings.


#include "BruteSetNextWaypointBTTaskNode.h"
#include "BruteAIController.h"

EBTNodeResult::Type UBruteSetNextWaypointBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABruteAIController* BruteAIController = Cast<ABruteAIController>(OwnerComp.GetOwner());

	BruteAIController->SetNextWaypoint();

	return EBTNodeResult::Succeeded;
}

FString UBruteSetNextWaypointBTTaskNode::GetStaticDescription() const
{
	return TEXT("Set the current waypoint of the AI");
}
