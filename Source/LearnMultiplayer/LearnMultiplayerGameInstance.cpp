// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnMultiplayerGameInstance.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

ULearnMultiplayerGameInstance::ULearnMultiplayerGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GAME INSTANCE [CONSTRUCT]"));
}

void ULearnMultiplayerGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GAME INSTANCE [INIT]"));
}

void ULearnMultiplayerGameInstance::Host()
{
	UEngine *Engine = GetEngine();
	if (Engine != nullptr)
	{
		Engine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, TEXT("Hosting..."));
	}

	UWorld *World = GetWorld();
	if (World != nullptr)
	{
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}

void ULearnMultiplayerGameInstance::Join(const FString &Address)
{
	UEngine *Engine = GetEngine();
	if (Engine != nullptr)
	{
		Engine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Joining [%s]"), *Address));
	}

	UWorld *World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController *MyPC = GetFirstLocalPlayerController(World);
	if (MyPC != nullptr)
	{
		Engine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Client travelling to [%s]..."), *Address));
		MyPC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}