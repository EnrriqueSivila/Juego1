// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloque.h"

// Sets default values
ABloque::ABloque()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla Estatica"));
	//asignar el meshcomp a la raiz de componente raiz
	RootComponent = MeshComp;

	//auto es una variebla automatica
	auto MeshCuboAux = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	auto MeshEsferaAux = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	auto MeshCilindroAux = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	auto MeshConoAux = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	//texturas
	auto MeshTexturaCilindro = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile.M_Tech_Hex_Tile'"));
	auto MeshTexturaCono = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'"));
	auto MeshTexturaEsfera = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/StarterContent/Materials/M_Water_Ocean.M_Water_Ocean'"));
	auto MeshTexturaCubo = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/StarterContent/Materials/M_Rock_Basalt.M_Rock_Basalt'"));
	
	if (MeshCuboAux.Succeeded()) {
		MeshCubo = MeshCuboAux.Object;
	}
	if (MeshEsferaAux.Succeeded()) {
		MeshEsfera = MeshEsferaAux.Object;
	}
	if (MeshCilindroAux.Succeeded()) {
		MeshCilindro = MeshCilindroAux.Object;
	}
	if (MeshConoAux.Succeeded()) {
		MeshCono = MeshConoAux.Object;
	}
	if (MeshTexturaCubo.Succeeded()) {
		MeshTexturaCuboA = MeshTexturaCubo.Object;
	}
	if (MeshTexturaEsfera.Succeeded()) {
		MeshTexturaEsferaA = MeshTexturaEsfera.Object;
	}
	if (MeshTexturaCilindro.Succeeded()) {
		MeshTexturaCilindroA = MeshTexturaCilindro.Object;
	}
	if (MeshTexturaCono.Succeeded()) {
		MeshTexturaConoA = MeshTexturaCono.Object;
	}
	MeshComp->SetStaticMesh(MeshCubo);

	seMueve = false;
	PosicionInicial = FVector(0, 0, 0);
	velocidad = 100.0f;
	distancia = 100.0f;
}

// Called when the game starts or when spawned
void ABloque::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABloque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CambiarForma();
	CambiarFormaPorTecladado();
	CambiarTextura();
	CambiarFormaPorTecladado();
	CambiarTexturaPorTeclado();
	MoverRampa(DeltaTime);
	/*if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::T)) {
		UE_LOG(LogTemp, Warning, TEXT("Se preciono la tecla T"));
		FVector NewLocation = GetActorLocation();
		seMueve = true;
		UE_LOG(LogTemp, Warning, TEXT("New Location: %s"), *NewLocation.ToString());
	}

	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::F)) {
		UE_LOG(LogTemp, Warning, TEXT("Se preciono la tecla F"));
		FVector NewLocation = GetActorLocation();
		seMueve = false;
		UE_LOG(LogTemp, Warning, TEXT("New Location: %s"), *NewLocation.ToString());
	}
	if (seMueve) {
		FVector NewLocation = GetActorLocation();
		NewLocation -= GetActorRightVector() * 500 * DeltaTime;
		SetActorLocation(NewLocation);
	}*/
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::T)) {
		UE_LOG(LogTemp, Warning, TEXT("Se preciono la tecla T"));
		seMueve = !seMueve;
	}
}

void ABloque::CambiarTextura() {
	if (TipoTextura == 1) {
		MeshComp->SetMaterial(0, MeshTexturaCuboA);
	}
	else if (TipoTextura == 2) {
		MeshComp->SetMaterial(0, MeshTexturaEsferaA);
	}
	else if (TipoTextura == 3) {
		MeshComp->SetMaterial(0, MeshTexturaCilindroA);
	}
	else if (TipoTextura == 4) {
		MeshComp->SetMaterial(0, MeshTexturaConoA);
	}
}

void ABloque::CambiarForma()
{
	if (TipoBloque > 4) {
		TipoBloque = 1;
	}
	if (TipoBloque == 1) {
		MeshComp->SetStaticMesh(MeshCubo);
	}
	else if (TipoBloque == 2) {
		MeshComp->SetStaticMesh(MeshEsfera);
	}
	else if (TipoBloque == 3) {
		MeshComp->SetStaticMesh(MeshCilindro);
	}
	else if (TipoBloque == 4) {
		MeshComp->SetStaticMesh(MeshCono);
	}
}

void ABloque::CambiarTexturaPorTeclado()
{
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Five)) {
		TipoTextura = 1;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Six)) {
		TipoTextura = 2;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Seven)) {
		TipoTextura = 3;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Eight)) {
		TipoTextura = 4;
	}
}
void ABloque::CambiarFormaPorTecladado() {

	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::One)) {
		TipoBloque = 1;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Two)) {
		TipoBloque = 2;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Three)) {
		TipoBloque = 3;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Four)) {
		TipoBloque = 4;
	}
}

void ABloque::MoverRampa(float DeltaTime) {
	if (seMueve) {
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorRightVector() * velocidad * DeltaTime;
		SetActorLocation(NewLocation);
		if (FVector::Dist(PosicionInicial, NewLocation) > distancia)
		{
			velocidad = -velocidad;
			PosicionInicial = NewLocation;
		}
	}
}