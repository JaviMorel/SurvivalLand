// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalPlayerController.h"
#include "SurvivalLandCharacter.h"
#include "Checkpoint.h"
#include "Kismet/GameplayStatics.h"
#include "SurvivalGameInstance.h"

void ASurvivalPlayerController::BeginPlay()
{
	TArray<AActor*> CheckpointsLevel;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckpoint::StaticClass(), CheckpointsLevel);
	if (CheckpointsLevel.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO WAYPOINTS FOUNDED"));
		return;
	}
	for (AActor* actor : CheckpointsLevel)
	{
		ACheckpoint* checkpoint = Cast<ACheckpoint>(actor);
		if(checkpoint != nullptr)
		{
			Checkpoints.Add(checkpoint);
		}
	}

	USurvivalGameInstance* GameInstance = Cast<USurvivalGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance == nullptr) return;

	NextCheckpointID = GameInstance->CheckpointID + 1;
	
	SetActiveCurrentCheckpoint();

	APawn* aPawn = GetPawn();
	ASurvivalLandCharacter* SurvivalPlayer = Cast<ASurvivalLandCharacter>(aPawn);
	if (SurvivalPlayer == nullptr) return;
	
	if(LastCheckpoint != nullptr)
	{
		SurvivalPlayer->SetActorLocation(LastCheckpoint->GetActorLocation() + FVector(0.f, 0.f, 200.f));
		SetControlRotation(LastCheckpoint->GetActorRotation());
		SurvivalPlayer->SetActorRotation(LastCheckpoint->GetActorRotation());
	}

}

void ASurvivalPlayerController::SetActiveCurrentCheckpoint()
{
	for (ACheckpoint* checkpoint : Checkpoints)
	{
		if(checkpoint->ID == NextCheckpointID)
		{
			checkpoint->ActivateCheckpoint();
		}
		else
		{
			if (checkpoint->ID == NextCheckpointID - 1)
			{
				LastCheckpoint = checkpoint;
			}
			checkpoint->DisableCheckpoint();
		}
	}
}

void ASurvivalPlayerController::UpdateCurrentCheckpoint(int IDCheckpoint)
{
	if (IDCheckpoint >= Checkpoints.Num()) return;
	if (Checkpoints.Num() <= 0) return;

	LastCheckpoint = Checkpoints[IDCheckpoint];
	
	NextCheckpointID = IDCheckpoint;
	++NextCheckpointID;
	SetActiveCurrentCheckpoint();
}

void ASurvivalPlayerController::SetPlayerToCheckpoint()
{
	if (Checkpoints.Num() <= 0) return;

	APawn* aPawn = GetPawn();
	ASurvivalLandCharacter* SurvivalPlayer = Cast<ASurvivalLandCharacter>(aPawn);
	if (SurvivalPlayer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PLAYER NOT FOUND"));
		return;
	}
	
	if(LastCheckpoint != nullptr)
	{
		SurvivalPlayer->SetActorLocation(LastCheckpoint->GetActorLocation() + FVector(0.f, 0.f, 200.f));
		SetControlRotation(LastCheckpoint->GetActorRotation());
		SurvivalPlayer->SetActorRotation(LastCheckpoint->GetActorRotation());
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Last Checkpoint doesn't get"));
}


void ASurvivalPlayerController::SetTutorialMode()
{
	SetCanJump(false);
}

void ASurvivalPlayerController::SetCanJump(bool NewValue)
{
	APawn* aPawn = GetPawn();
	ASurvivalLandCharacter* SurvivalPlayer = Cast<ASurvivalLandCharacter>(aPawn);
	if (SurvivalPlayer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PLAYER NOT FOUND"));
		return;
	}
	SurvivalPlayer->bCanJump = NewValue;
}

void ASurvivalPlayerController::SetDeadPlayer_Implementation()
{
	
}