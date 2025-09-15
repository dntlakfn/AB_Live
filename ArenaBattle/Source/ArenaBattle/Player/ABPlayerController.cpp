// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

void AABPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	AddPitchInput(15.0f);
}
