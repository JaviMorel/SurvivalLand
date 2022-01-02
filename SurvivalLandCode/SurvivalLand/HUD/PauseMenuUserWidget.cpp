// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/ScaleBox.h"


void UPauseMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UPauseMenuUserWidget::OpenPauseMenuBox()
{
	PauseMenuBox->SetVisibility(ESlateVisibility::Visible);
	SaveGameBox->SetVisibility(ESlateVisibility::Collapsed);
	ControlsBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UPauseMenuUserWidget::OpenSaveGameBox()
{
	PauseMenuBox->SetVisibility(ESlateVisibility::Collapsed);
	SaveGameBox->SetVisibility(ESlateVisibility::Visible);
	ControlsBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UPauseMenuUserWidget::OpenControlsBox()
{
	PauseMenuBox->SetVisibility(ESlateVisibility::Collapsed);
	SaveGameBox->SetVisibility(ESlateVisibility::Collapsed);
	ControlsBox->SetVisibility(ESlateVisibility::Visible);
}
