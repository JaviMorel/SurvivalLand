// Fill out your copyright notice in the Description page of Project Settings.


#include "BruteReachLastLocBTTaskNode.h"
#include "BruteAIController.h"

EBTNodeResult::Type UBruteReachLastLocBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABruteAIController* BruteAIController = Cast<ABruteAIController>(OwnerComp.GetOwner());

	BruteAIController->ReachLastLocationOfPlayer();

	return EBTNodeResult::Succeeded;
}

FString UBruteReachLastLocBTTaskNode::GetStaticDescription() const
{
	return TEXT("Move to the player detected");
}
