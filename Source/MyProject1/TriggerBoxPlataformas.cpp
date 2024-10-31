#include "TriggerBoxPlataformas.h"
#include "Engine/Engine.h"
#include "Engine/StaticMeshActor.h"
#include "MyProject1Character.h"

// Constructor
ATriggerBoxPlataformas::ATriggerBoxPlataformas()
{
    // Configurar los eventos de colisión
    OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxPlataformas::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &ATriggerBoxPlataformas::OnOverlapEnd);
}

void ATriggerBoxPlataformas::BeginPlay()
{
    Super::BeginPlay();
}


void ATriggerBoxPlataformas::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && (OtherActor != this))
    {
        // Mostrar mensaje de inicio de colisión para depuración

        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Overlap Begin"));
        AMyProject1Character* MyCharacter = Cast<AMyProject1Character>(OtherActor);
        if (MyCharacter) {
            MoverPlataforma(100.0f);
        }
    }
}

void ATriggerBoxPlataformas::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && (OtherActor != this))
    {
        // Mostrar mensaje de final de colisión para depuración
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
        AMyProject1Character* MyCharacter = Cast<AMyProject1Character>(OtherActor);
    }
}

// Función para mover plataformas
void ATriggerBoxPlataformas::MoverPlataforma(float distance)
{
    // Iterar sobre cada plataforma en la lista y moverla
    for (AStaticMeshActor* piso : plataforma)
    {
        if (piso)
        {
            // Obtener la ubicación actual de la plataforma
            UStaticMeshComponent* MeshComponent = piso->GetStaticMeshComponent();
            if (MeshComponent)
            {
                MeshComponent->SetMobility(EComponentMobility::Movable);

                FVector NewLocation = piso->GetActorLocation();
                NewLocation.Z -= distance;
                piso->SetActorLocation(NewLocation);
            }
        }
    }
}





