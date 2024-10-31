// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinClass.h"

#define LOCTEXT_NAMESPACE "CoinClass"

void CoinClass::Construct(const FArguments& InArgs)
{
    CoinText = FText::FromString("Coins: 0"); // Inicializa el texto de las monedas
    /*ChildSlot
        [
            SNew(SOverlay)
                .Visibility(EVisibility::HitTestInvisible) // Hace que el widget no sea interactuable
                + SOverlay::Slot()
                .HAlign(HAlign_Left)  // Posicionar en la parte izquierda
                .VAlign(VAlign_Top)   // Posicionar en la parte superior
                [
                    SNew(SBorder)
                        .BorderBackgroundColor(FLinearColor(0.0f, 0.0f, 1.0f, 0.5f)) // Color azul semitransparente para visualizar el área
                        .Padding(5.0f) // Añade un pequeño padding para ver los límites más claramente
                        [
                            SNew(SBox)
                                .WidthOverride(200.0f)  // Ancho del widget
                                .HeightOverride(50.0f)  // Altura del widget
                                [
                                    SNew(STextBlock)
                                        .Text(CoinText)
                                        .ColorAndOpacity(FLinearColor::White) // Cambia el color del texto si es necesario
                                        .Justification(ETextJustify::Center) // Centra el texto dentro del SBox si es necesario
                                ]
                        ]
                ]
        ];*/

    FSlateFontInfo FontInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
    FontInfo.Size = 20.0f;


    UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/StarterContent/Textures/T_CobbleStone_Rough_D.T_CobbleStone_Rough_D'"));

    ChildSlot
        [
            SNew(SOverlay)
                + SOverlay::Slot()
                .HAlign(HAlign_Left)
                .VAlign(VAlign_Top)
                [
                    SAssignNew(CoinCountText, STextBlock)
                        .Text(FText::FromString("Coins: 0"))
                        .ColorAndOpacity(FLinearColor::White)
                        .Font(FontInfo)
                ]
        ];

}

void CoinClass::SetCoinCount(int32 NewCount)
{
    //CoinText = FText::FromString(FString::Printf(TEXT("Coins: %d"), Value)); // Actualiza el texto de las monedas
    //CoinCountText->SetText(CoinText); // Actualiza el texto de las monedas
    if (CoinCountText.IsValid())
    {
        CoinCountText->SetText(FText::Format(NSLOCTEXT("HUD", "CoinCount", "Coins: {0}"), FText::AsNumber(NewCount)));
    }
}

/*void CoinClass::OwningHUD(ACoinHUD* NewOwner)
{
    if (NewOwner)
    {
        OwnerHUD = NewOwner;
    }
}

void CoinClass::UpdateCoinCount(int32 Value)
{
    CoinText = FText::FromString(FString::Printf(TEXT("Coins: %d"), Value)); // Actualiza el texto de las monedas
}*/

#undef LOCTEXT_NAMESPACE
