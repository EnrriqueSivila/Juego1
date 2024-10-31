// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinHUD.h"
#include "CoinClass.h"
#include "Engine/Engine.h"
#include "Widgets/SWeakWidget.h"
#include "GameFramework/PlayerController.h"

void ACoinHUD::BeginPlay()
{
	Super::BeginPlay();
	showCoinWidget();
}


void ACoinHUD::showCoinWidget()
{
	// Si el widget de monedas no ha sido creado, se crea
	if (GEngine && GEngine->GameViewport)
	{
		// Se crea el widget de monedas
		CoinWidget = SNew(CoinClass).OwningHUD(this);

		// Se agrega el widget de monedas al contenedor de widgets
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(CoinWidgetContainer, SWeakWidget).PossiblyNullContent(CoinWidget.ToSharedRef())); // Toma el widget de monedas y lo agrega al contenedor de widgets
		// Se muestra el cursor del mouse y se establece el modo de entrada del jugador
		if (PlayerOwner)
		{
			// Se muestra el cursor del mouse
			PlayerOwner->bShowMouseCursor = true;
			// Se establece el modo de entrada del jugador
			//PlayerOwner->SetInputMode(FInputModeUIOnly());
			PlayerOwner->SetInputMode(FInputModeGameAndUI());
		}
	}
}

void ACoinHUD::UpdateCoinWidget(int32 NewCount)
{
	CoinCount = NewCount;
	// Si el widget de monedas ha sido creado, se actualiza el texto
	if (CoinWidget.IsValid())
	{
		CoinWidget->SetCoinCount(CoinCount);
	}
}