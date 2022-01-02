// Fill out your copyright notice in the Description page of Project Settings.


#include "BruteCheckPlayerBTService.h"
#include "BruteAIController.h"

void UBruteCheckPlayerBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ABruteAIController* BruteAIController = Cast<ABruteAIController>(OwnerComp.GetOwner());

	BruteAIController->CheckPlayer();
}