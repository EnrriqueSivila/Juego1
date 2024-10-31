// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bloque.generated.h"

UCLASS()
class MYPROJECT1_API ABloque : public AActor
{
	GENERATED_BODY()
	
	

public:	
	// Sets default values for this actor's properties
	ABloque();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Caracteristicas Bloque")
	int TipoBloque;//1->Cubo, 2->Esfera, 3->Cilindro,4->Cono
	UStaticMeshComponent* MeshComp;
	UStaticMesh* MeshCubo;
	UStaticMesh* MeshEsfera;
	UStaticMesh* MeshCilindro;
	UStaticMesh* MeshCono;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Caracteristicas Bloque")
	int TipoTextura;
	UMaterial* MeshTexturaCuboA;
	UMaterial* MeshTexturaEsferaA;
	UMaterial* MeshTexturaCilindroA;
	UMaterial* MeshTexturaConoA;

	FVector PosicionInicial;
	float velocidad;
	float distancia;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CambiarForma();
	void CambiarFormaPorTecladado();
	void CambiarTextura();
	void CambiarTexturaPorTeclado();
	bool seMueve = false;
	void MoverRampa(float DeletaTime);
};
