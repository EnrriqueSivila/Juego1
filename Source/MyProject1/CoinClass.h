// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h" 
#include "SlateExtras.h"

/**
 *
 */
class CoinClass : public SCompoundWidget
{
public:

	// Declaracion de un argumento de tipo TWeakObjectPtr que se utilizara para referenciar a la clase ACoinHUD
	SLATE_BEGIN_ARGS(CoinClass)
		{}

		// SLATE_ARGUMENT es una macro que se utiliza para declarar un argumento de tipo TWeakObjectPtr que se utilizara para referenciar a la clase ACoinHUD
		SLATE_ARGUMENT(TWeakObjectPtr<class ACoinHUD>, OwningHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class ACoinHUD> OwningHUD;

	// Funcion que se encarga de actualizar el texto de las monedas
	void SetCoinCount(int32 NewCount);

	// Funcion que se encarga de manejar el foco del teclado en el widget si es necesario
	virtual bool SupportsKeyboardFocus() const override { return true; }

	//variable para mostrar el texto de las monedas
	FText CoinText;

	//variable para almacenar el texto de las monedas
	TSharedPtr<STextBlock> CoinCountText;
};