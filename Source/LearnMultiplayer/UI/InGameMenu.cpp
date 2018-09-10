// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool r = Super::Initialize();
	if (!r) return false;

	if (!ensure(BackToGameButton != nullptr)) return false;
	BackToGameButton->OnClicked.AddDynamic(this, &UInGameMenu::OnBackToGameClicked);

	if (!ensure(QuitGameButton != nullptr)) return false;
	QuitGameButton->OnClicked.AddDynamic(this, &UInGameMenu::OnQuitGameClicked);

	// QuitGameButton

	return true;
}

void UInGameMenu::OnLevelRemovedFromWorld(ULevel *InLevel, UWorld *InWorld)
{
	this->RemoveFromViewport();

	ensure(InWorld != nullptr);

	APlayerController *MyPC = InWorld->GetFirstPlayerController();
	if (!ensure(MyPC != nullptr)) return;

	// Configure the input mode for the UI widget
	FInputModeGameOnly InputModeData;

	MyPC->SetInputMode(InputModeData); // Set the UI input mode we configured
	MyPC->bShowMouseCursor = false;
}

void UInGameMenu::OnBackToGameClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("BACK TO GAME CLICKED"));
}

void UInGameMenu::OnQuitGameClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("QUIT GAME CLICKED"));
}
