// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CoinHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT1_API ACoinHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	// Variable para almacenar el widget de monedas
	TSharedPtr<class CoinClass> CoinWidget;
	// Variable para almacenar el contenedor del widget de monedas
	TSharedPtr<class SWidget> CoinWidgetContainer;

	virtual void BeginPlay() override;

	int32 CoinCount = 0;

	//Función para actualizar el contedo del widget de monedas


public:
	void UpdateCoinWidget(int32 NewCount);
	void showCoinWidget();
	//void hideCoinWidget();
	//void setCoinCount(int32 count);
	//void addCoin();
};
