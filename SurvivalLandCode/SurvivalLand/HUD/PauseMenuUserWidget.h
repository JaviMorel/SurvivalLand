// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuUserWidget.generated.h"

class USurvivalSaveGame;
class UScaleBox;

/**
 * 
 */
UCLASS()
class SURVIVALLAND_API UPauseMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;
	
public:
	const FString SaveSlot = "Whispers";

	UPROPERTY(meta = (BindWidget))
	UScaleBox* PauseMenuBox;

	UPROPERTY(meta = (BindWidget))
	UScaleBox* SaveGameBox;

	UPROPERTY(meta = (BindWidget))
	UScaleBox* ControlsBox;
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void OpenPauseMenuBox();
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void OpenSaveGameBox();
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void OpenControlsBox();
};
