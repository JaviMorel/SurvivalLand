// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

class USurvivalSaveGame;
class UScaleBox;
class UButton;
/**
 * 
 */
UCLASS()
class SURVIVALLAND_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;
	
public:
	const FString SaveSlot = "SurvivalLand";

	UPROPERTY(meta = (BindWidget))
	UScaleBox* MainMenuBox;

	UPROPERTY(meta = (BindWidget))
	UScaleBox* StoryModeBox;

	UPROPERTY(meta = (BindWidget))
	UScaleBox* ControlsBox;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void OpenMainMenuBox();
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void OpenStoryModeBox();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void OpenControlsBox();

	UFUNCTION(BlueprintCallable,Category = "HUD")
	void GetSurvivalSaveGame();

	UPROPERTY()
	USurvivalSaveGame* SurvivalSaveGame;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	USurvivalSaveGame* GetLoadedSurvivalSaveGame() { return SurvivalSaveGame; }

	UPROPERTY()
	bool isAGameSaved = false;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	bool GetIsAGameSaved() { return isAGameSaved; }

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void QuitGame();

	UPROPERTY(meta = (BindWidget))
	UButton* DeleteGameButton;
};
