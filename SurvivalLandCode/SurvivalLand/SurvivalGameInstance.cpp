// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalGameInstance.h"
#include "SurvivalSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USurvivalGameInstance::SaveGameToSlot()
{
	USurvivalSaveGame* SurvivalSaveGame = Cast<USurvivalSaveGame>(UGameplayStatics::CreateSaveGameObject(USurvivalSaveGame::StaticClass()));
	if (SurvivalSaveGame == nullptr) return;

	SurvivalSaveGame->Level = CurrentLevel;
	SurvivalSaveGame->CheckpointID = CheckpointID;
	
	UGameplayStatics::SaveGameToSlot(SurvivalSaveGame, SaveSlot, 0);

}

void USurvivalGameInstance::LoadGameToSlot()
{
	USurvivalSaveGame* SaveGame = Cast<USurvivalSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	if (SaveGame == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Survival Save Game doesn't exist"));
		return;
	}

	CurrentLevel = SaveGame->Level;
	CheckpointID = SaveGame->CheckpointID;
}


void USurvivalGameInstance::DeleteGameToSlot()
{
	UGameplayStatics::DeleteGameInSlot(SaveSlot, 0);
}