// Fill out your copyright notice in the Description page of Project Settings.


#include "Moneda.h"
// Sets default values
AMoneda::AMoneda()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;

    //StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'
    // Create and attach the mesh component
    CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
    CoinMesh->SetupAttachment(RootComponent);

    // Set the collision box size to match the coin
    CollisionComponent->SetBoxExtent(FVector(50.f,50.f, 20.f)); // Adjust size as needed


    static ConstructorHelpers::FObjectFinder<UStaticMesh> CoinMeshAsset(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    if (CoinMeshAsset.Succeeded())
    {
        CoinMesh->SetStaticMesh(CoinMeshAsset.Object);
    }

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Material'/Game/StarterContent/Materials/Moneda.Moneda'"));
	if (MaterialAsset.Succeeded())
	{
		MaterialMoneda = MaterialAsset.Object;
		CoinMesh->SetMaterial(0, MaterialMoneda);
	}

    FRotator NewRotation = GetActorRotation();
    NewRotation.Pitch = 90.0f; // Set the Yaw (Y-axis rotation) to 90 degrees
    SetActorRotation(NewRotation);

    FVector NewScale = GetActorScale3D();
    NewScale.Z = 0.2f; // Adjust the Z scale to make it thin like a coin
    SetActorScale3D(NewScale);

    CollisionComponent->SetCollisionProfileName(TEXT("Trigger"));
    CoinMesh->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void AMoneda::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMoneda::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += 1.0f + DeltaTime;
    SetActorRotation(NewRotation);
}

void AMoneda::Ocultar()
{
    CoinMesh->SetHiddenInGame(true);
}


