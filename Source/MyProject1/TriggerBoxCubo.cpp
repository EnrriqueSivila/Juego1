// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBoxCubo.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "MyProject1Character.h"

ATriggerBoxCubo::ATriggerBoxCubo()
{
    OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxCubo::OnOverlapBegin);
}

void ATriggerBoxCubo::BeginPlay()
{
    Super::BeginPlay();
}

void ATriggerBoxCubo::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && (OtherActor != this))
    {
		AMyProject1Character* MyCharacter = Cast<AMyProject1Character>(OtherActor);
        if (MyCharacter)
        {
            if (tipo == 1) {              
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Aumenta Vidas"));
                MyCharacter->AumentarVidas();
            }
            else if (tipo == 2) {              
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Quita Vida"));
                MyCharacter->DisminuirVidas();
            }
            else if (tipo == 3) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Ganaste Felicidades"));
            }
            else if (tipo == 4) {
                
            }
        }
    }
}
