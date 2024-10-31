// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject1GameMode.h"
#include "MyProject1Character.h"
#include "GamePlayerController.h"
#include "CoinHUD.h"
#include "UObject/ConstructorHelpers.h"

AMyProject1GameMode::AMyProject1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = AGamePlayerController::StaticClass();
	HUDClass = ACoinHUD::StaticClass();

}
