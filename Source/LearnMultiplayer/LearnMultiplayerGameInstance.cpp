// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnMultiplayerGameInstance.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "UI/MainMenu.h"

ULearnMultiplayerGameInstance::ULearnMultiplayerGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GAME INSTANCE [CONSTRUCT]"));
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/LearnMultiplayer/UI/WBP_MainMenu"));
	if (MenuBPClass.Class != NULL)
	{
		MenuClass = MenuBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/LearnMultiplayer/UI/WBP_InGameMenu"));
	if (InGameMenuBPClass.Class != NULL)
	{
		InGameMenuClass = InGameMenuBPClass.Class;
	}
}

void ULearnMultiplayerGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GAME INSTANCE [INIT]"));
	UE_LOG(LogTemp, Warning, TEXT("Found class [%s]"), *MenuClass->GetName());
}

void ULearnMultiplayerGameInstance::LoadMenu()
{
	if (MenuClass != NULL)
	{
		// Instantiate the main menu widget
		Menu = CreateWidget<UMainMenu>(this, MenuClass, FName("MainMenu"));
		if (!ensure(Menu != nullptr)) return;

		Menu->Setup();
		Menu->SetMenuInterface(this); // Connect this gameinstance to the menu widget for IMenuInterface implementation
	}
}

void ULearnMultiplayerGameInstance::LoadInGameMenu()
{
	if (InGameMenuClass != NULL)
	{
		// Instantiate the main menu widget
		UUserWidget *Menu = CreateWidget<UUserWidget>(this, InGameMenuClass, FName("InGameMenu"));
		if (!ensure(InGameMenu != nullptr)) return;
	}
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