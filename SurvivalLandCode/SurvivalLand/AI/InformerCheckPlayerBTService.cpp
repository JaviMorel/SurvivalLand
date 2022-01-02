// Fill out your copyright notice in the Description page of Project Settings.


#include "InformerCheckPlayerBTService.h"
#include "InformerAIController.h"

void UInformerCheckPlayerBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AInformerAIController* InformerAIController = Cast<AInformerAIController>(OwnerComp.GetOwner());

	InformerAIController->CheckPlayer();
}
