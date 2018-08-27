// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LearnMultiplayerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEARNMULTIPLAYER_API ULearnMultiplayerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	ULearnMultiplayerGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init() override;
	
	/* Compatible for execs: PC's, Pawns, Huds, Cheat managers, game modes, game instances*/
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString &Address);
};
