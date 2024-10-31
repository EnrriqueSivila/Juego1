// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PeonPawn.generated.h"

UCLASS()
class MYPROJECT1_API APeonPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APeonPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caracteristicas Figura")
	int tipoFigura;//1->Cubo, 2->Esfera, 3->Cilindro,4->Cono

	UStaticMeshComponent* MeshComp;
	UStaticMesh* MeshCubo;
	UStaticMesh* MeshCono;
	UStaticMesh* MeshCilindro;
	UStaticMesh* MeshEsfera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caracteristicas Figura")
	int tipoTextura;
	UMaterial* MaterialCubo;
	UMaterial* MaterialCono;
	UMaterial* MaterialCilindro;
	UMaterial* MaterialCirculo;

	FVector PosicionInicial;
	float velocidad;
	float distancia;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	UStaticMeshComponent* StaticMesh;
	void CambiarMalla();
	void CambiarMallaPorTecladado();
	void cambiarDisfraz();
	void cambiarDisfrazPorTeclado();
	bool seMueve = false;  
	void MoverRampa(float DeletaTime);
};
