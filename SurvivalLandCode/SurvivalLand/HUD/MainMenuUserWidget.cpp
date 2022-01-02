// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUserWidget.h"
#include "../SurvivalSaveGame.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/ScaleBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), this, EMouseLockMode::LockAlways);

	DeleteGameButton->SetVisibility(ESlateVisibility::Collapsed);
#if WITH_EDITOR
	DeleteGameButton->SetVisibility(ESlateVisibility::Visible);
#endif
	
	GetSurvivalSaveGame();
}

void UMainMenuUserWidget::OpenMainMenuBox()
{
	MainMenuBox->SetVisibility(ESlateVisibility::Visible);
	StoryModeBox->SetVisibility(ESlateVisibility::Collapsed);
	ControlsBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainMenuUserWidget::OpenStoryModeBox()
{
	MainMenuBox->SetVisibility(ESlateVisibility::Collapsed);
	StoryModeBox->SetVisibility(ESlateVisibility::Visible);
	ControlsBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainMenuUserWidget::OpenControlsBox()
{
	MainMenuBox->SetVisibility(ESlateVisibility::Collapsed);
	StoryModeBox->SetVisibility(ESlateVisibility::Collapsed);
	ControlsBox->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuUserWidget::GetSurvivalSaveGame()
{
	USurvivalSaveGame* SaveGame = Cast<USurvivalSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	if (SaveGame != nullptr)
	{
		SurvivalSaveGame = SaveGame;
		isAGameSaved = true;
	}
	else
	{
		isAGameSaved = false;
	}
}

void UMainMenuUserWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Background, true);
}