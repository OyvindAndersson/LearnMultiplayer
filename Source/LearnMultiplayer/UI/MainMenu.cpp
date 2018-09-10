// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
//#include "Button.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool r = Super::Initialize();
	if (!r) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostClicked);
	
	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinClicked);

	if (!ensure(JoinIpButton != nullptr)) return false;
	JoinIpButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinIpClicked);

	if (!ensure(CancelJoinButton != nullptr)) return false;
	CancelJoinButton->OnClicked.AddDynamic(this, &UMainMenu::OnCancelJoinClicked);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface *MenuInterface)
{
	this->MenuInterface = MenuInterface;

	ensure(this->MenuInterface != nullptr);
}

void UMainMenu::Setup()
{
	UWorld *World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController *MyPC = World->GetFirstPlayerController();
	if (!ensure(MyPC != nullptr)) return;

	this->AddToViewport(); // Add the umg widget to the viewport

	// Configure the input mode for the UI widget
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget()); // Get underlying SWidget
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // Don't lock, be able to move mouse all over the editor

	MyPC->SetInputMode(InputModeData); // Set the UI input mode we configured
	MyPC->bShowMouseCursor = true; // We must also opt to show the cursor, as it will dissapear on focus if not.
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel *InLevel, UWorld *InWorld)
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

void UMainMenu::OnHostClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("HOSTING SERVER"));

	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::OnJoinClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("GOTO JOIN MENU"));

	if (MenuSwitcher != nullptr && JoinMenu != nullptr)
	{
		MenuSwitcher->SetActiveWidget(JoinMenu);
	}
	
}

void UMainMenu::OnJoinIpClicked()
{
	if (MenuInterface != nullptr)
	{
		if (!ensure(AddressTextBox != nullptr)) return;
		const FString input = AddressTextBox->GetText().ToString();

		UE_LOG(LogTemp, Warning, TEXT("JOIN BY IP - [%s]"), *input);

		MenuInterface->Join(input);
	}
}

void UMainMenu::OnCancelJoinClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("CANCEL JOIN - GOTO MAIN MENU"));

	if (MenuSwitcher != nullptr && MainMenu != nullptr)
	{
		MenuSwitcher->SetActiveWidget(MainMenu);
	}
}
