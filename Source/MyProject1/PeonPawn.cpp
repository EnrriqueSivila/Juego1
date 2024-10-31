// Fill out your copyright notice in the Description page of Project Settings.


#include "PeonPawn.h"

// Sets default values
APeonPawn::APeonPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	RootComponent = StaticMesh;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCirculoAux(TEXT("/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialCirculoAux.Succeeded())
	{
		MaterialCirculo = MaterialCirculoAux.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCilindroAux(TEXT("/Game/StarterContent/Materials/M_CobbleStone_Smooth.M_CobbleStone_Smooth"));
	if (MaterialCilindroAux.Succeeded())
	{
		MaterialCilindro = MaterialCilindroAux.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialConoAux(TEXT("Material'/Game/Geometry/Texturas_M/Material2.Material2'"));
	if (MaterialConoAux.Succeeded())
	{
		MaterialCono = MaterialConoAux.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCuboAux(TEXT("Material'/Game/Geometry/Texturas_M/Material1.Material1'"));
	if (MaterialCuboAux.Succeeded())
	{
		MaterialCubo = MaterialCuboAux.Object;
	}
	auto MeshCuboAux = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	auto MeshEsferaAux = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	auto MeshCilindroAux = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	auto MeshConoAux = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	
	if (MeshConoAux.Succeeded())
	{
		MeshCono = MeshConoAux.Object;
	}
	if (MeshCuboAux.Succeeded())
	{
		MeshCubo = MeshCuboAux.Object;
	}
	if (MeshCilindroAux.Succeeded())
	{
		MeshCilindro = MeshCilindroAux.Object;
	}
	if (MeshEsferaAux.Succeeded())
	{
		MeshEsfera = MeshEsferaAux.Object;
	}
	
	StaticMesh->SetStaticMesh(MeshCubo);

	seMueve = false;
	PosicionInicial = FVector(0,0,0);
	velocidad = 100.0f;
	distancia = 100.0f;
}

// Called when the game starts or when spawned
void APeonPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APeonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CambiarMalla();
	CambiarMallaPorTecladado();
	cambiarDisfraz();
	cambiarDisfrazPorTeclado();
	MoverRampa(DeltaTime);
	/*cambiarDisfraz();*/
	//Mover el bloque automaticamente
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
		NewLocation += GetActorRightVector() * 500 * DeltaTime;
		SetActorLocation(NewLocation);
	}*/

	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::T)) {
		UE_LOG(LogTemp, Warning, TEXT("Se preciono la tecla T"));
		seMueve = !seMueve;
	}	
}

// Called to bind functionality to input
void APeonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APeonPawn::CambiarMalla()
{
	if (tipoFigura == 1)
	{
		StaticMesh->SetStaticMesh(MeshCubo);
	}
	else if (tipoFigura == 2)
	{
		StaticMesh->SetStaticMesh(MeshEsfera);
	}
	else if (tipoFigura == 3)
	{
		StaticMesh->SetStaticMesh(MeshCilindro);
	}
	else if (tipoFigura == 4)
	{
		StaticMesh->SetStaticMesh(MeshCono);
	}
}
void APeonPawn::CambiarMallaPorTecladado() {

	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::One)) {
		tipoFigura = 1;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Two)) {
		tipoFigura = 2;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Three)) {
		tipoFigura = 3;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Four)) {
		tipoFigura = 4;
	}
}

void APeonPawn::cambiarDisfraz()
{
	if (tipoTextura == 1)
	{
		StaticMesh->SetMaterial(0, MaterialCubo);
		//StaticMesh->SetStaticMesh(MeshCubo);

	}
	else if (tipoTextura == 2)
	{
		//StaticMesh->SetStaticMesh(MeshCono);
		StaticMesh->SetMaterial(0, MaterialCono);
	}
	else if (tipoTextura == 3)
	{
		//StaticMesh->SetStaticMesh(MeshCilindro);
		StaticMesh->SetMaterial(0, MaterialCilindro);
	}
	else if (tipoTextura == 4)
	{
		//StaticMesh->SetStaticMesh(MeshEsfera);
		StaticMesh->SetMaterial(0, MaterialCirculo);
	}
}

void APeonPawn::MoverRampa(float DeltaTime) {
	if (seMueve) {
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorRightVector() * velocidad * DeltaTime;
		SetActorLocation(NewLocation);
		if(FVector::Dist(PosicionInicial, NewLocation)>distancia)
		{
			velocidad = -velocidad;
			PosicionInicial = NewLocation;
		}
	}
}

void APeonPawn::cambiarDisfrazPorTeclado()
{
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Five)) {
		tipoTextura = 1;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Six)) {
		tipoTextura = 2;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Seven)) {
		tipoTextura = 3;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Eight)) {
		tipoTextura = 4;
	}
}
