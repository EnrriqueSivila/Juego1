// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerBoxGraw.h"
#include "MyProject1Character.h"

void ATriggerBoxGraw::BeginPlay()
{
	Super::BeginPlay();
}

ATriggerBoxGraw::ATriggerBoxGraw()
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxGraw::OnOverlapBegin);
}
void ATriggerBoxGraw::OnOverlapBegin(class AActor* OverlappedActor, AActor* OtherActor)
{
    
    if (OtherActor && (OtherActor != this)) {
        AMyProject1Character* MyCharacter = Cast<AMyProject1Character>(OtherActor);
        if (MyCharacter) {
            contador = contador + 1;
            if (tipo == 1) {
                MyCharacter->AumentarTamanio();
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Aumenta Tamanio"));
            }
            if (tipo == 3) {
                MyCharacter->DisminuirTamanio();
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Disminuye Tamanio"));
            }
        UE_LOG(LogTemp, Warning, TEXT("Contador: %d"), contador);
        }
    }
}