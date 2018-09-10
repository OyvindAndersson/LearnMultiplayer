// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/MenuInterface.h"
#include "LearnMultiplayerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEARNMULTIPLAYER_API ULearnMultiplayerGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	ULearnMultiplayerGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init() override;

	/* Exec ufunctions compatible with: PC's, Pawns, Huds, Cheat managers, game modes, game instances*/

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadInGameMenu();
	
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString &Address);


private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu *Menu;
	class UInGameMenu *InGameMenu;
};
