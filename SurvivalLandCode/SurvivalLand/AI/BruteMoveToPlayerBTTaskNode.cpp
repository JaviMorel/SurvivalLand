// Fill out your copyright notice in the Description page of Project Settings.


#include "BruteMoveToPlayerBTTaskNode.h"
#include "BruteAIController.h"

EBTNodeResult::Type UBruteMoveToPlayerBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABruteAIController* BruteAIController = Cast<ABruteAIController>(OwnerComp.GetOwner());

	BruteAIController->MoveToPlayer();

	return EBTNodeResult::Succeeded;
}

FString UBruteMoveToPlayerBTTaskNode::GetStaticDescription() const
{
	return TEXT("Move to the player detected");
}

