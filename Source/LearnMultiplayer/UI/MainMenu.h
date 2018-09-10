// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class LEARNMULTIPLAYER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface *MenuInterface);

	void Setup();

protected:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(class ULevel *InLevel, class UWorld *InWorld) override;

private:

	// Main Menu Controls ------------------

	UPROPERTY(meta = (BindWidget))
	class UButton *HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinButton;

	// Join SubMenu Controls ------------------

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinIpButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CancelJoinButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *AddressTextBox;

	// Menus ------------------

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher *MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget *MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget *JoinMenu;

	// Event Handlers ------------------

	UFUNCTION()
	void OnHostClicked();

	UFUNCTION()
	void OnJoinClicked();

	UFUNCTION()
	void OnJoinIpClicked();

	UFUNCTION()
	void OnCancelJoinClicked();

	IMenuInterface *MenuInterface;
	
};
