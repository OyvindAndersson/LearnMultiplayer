// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class LEARNMULTIPLAYER_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(class ULevel *InLevel, class UWorld *InWorld) override;
	
private:

	UPROPERTY(meta = (BindWidget))
	class UButton *BackToGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *QuitGameButton;

	UFUNCTION()
	void OnBackToGameClicked();

	UFUNCTION()
	void OnQuitGameClicked();
};
