#include "TriggerBoxSpawn.h"
#include "MyProject1Character.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "PeonPawn.h"

void ATriggerBoxSpawn::BeginPlay()
{
	Super::BeginPlay();
}

ATriggerBoxSpawn::ATriggerBoxSpawn()
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxSpawn::OnOverlapBegin);
}

void ATriggerBoxSpawn::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		if (isFirstTime)
		{
		UWorld* const World = GetWorld();
			if (OtherActor && OtherActor)
			{
				APeonPawn* nuevoShape = World->SpawnActor<APeonPawn>(OtherActor->GetActorLocation() = FVector(1210, -990, 570), OtherActor->GetActorRotation() = FRotator(0.0f, 0.0f, 0.0f));
				APeonPawn* nuevoShape2 = World->SpawnActor<APeonPawn>(OtherActor->GetActorLocation() = FVector(1236.599976 , -1510, 530), OtherActor->GetActorRotation() = FRotator(0.0f, 0.0f, 0.0f));
			}	
		}
	}
}
