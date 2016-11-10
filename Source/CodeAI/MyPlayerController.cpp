// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeAI.h"
#include "MyPlayerController.h"
#include "PlayerUI.h"
#include "ItemWidget.h"
#include "CodeAICharacter.h"

void AMyPlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (PlayerUIBP){
		//Create the Inventory Widget based on the Blueprint reference we will input from within the Editor
		PlayerUIRef = CreateWidget<UPlayerUI>(this, PlayerUIBP);
		PlayerUIRef->Show();
	}
	bIsLeftMenuOpen = false;
	bIsRightMenuOpen = false;
}

void AMyPlayerController::ToogleLeftMenu()
{
	ACodeAICharacter* Char = Cast<ACodeAICharacter>(GetPawn());
	if (Char) {

		if (bIsLeftMenuOpen) {
			bIsLeftMenuOpen = false;
			PlayerUIRef->HideLeftInventory();

			//Tell the game that we want to register inputs for our game only and not for our UI
			FInputModeGameOnly InputMode;
			SetInputMode(InputMode);
			SetPause(false);
		}
		else {
			bIsLeftMenuOpen = true;
			PlayerUIRef->ItemsArray = Char->GetInventory();
			PlayerUIRef->ShowLeftInventory();

			//Tell the game that we want to register inputs both for our game and UI
			FInputModeGameAndUI InputMode;
			SetInputMode(InputMode);
			SetPause(true);
		}
	}
}

void AMyPlayerController::ToogleCurrentItem()
{
	ACodeAICharacter* Char = Cast<ACodeAICharacter>(GetPawn());
	if (Char) {
		PlayerUIRef->ItemsArray = Char->GetInventory();
		PlayerUIRef->ToogleShowLeftItem();
	}
}

void AMyPlayerController::UpdateItem()
{
	PlayerUIRef->UpdateCurrentLeftItem();
}

void AMyPlayerController::MenuLeft()
{
	PlayerUIRef->PlayLeftMenuAnimation(false);
}

void AMyPlayerController::MenuRight()
{
	PlayerUIRef->PlayLeftMenuAnimation(true);
}