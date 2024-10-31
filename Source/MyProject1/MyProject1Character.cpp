// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProject1Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyProject1Character::AMyProject1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//DECLARAR.

	//sirve para cargar el objeto
	//SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'
	//SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin_Female.SK_Mannequin_Female'
	//SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'
 // Crear el componente de malla estática


	// Cargar las mallas
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshHombreAux(TEXT("/Game/Man/Mesh/Full/SK_Man_Full_04.SK_Man_Full_04"));
	/*if (MeshHombreAux.Succeeded())
	{
		MeshHombre = MeshHombreAux.Object;
	}*/

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshMujerAux(TEXT("SkeletalMesh'/Game/Man/Mesh/Full/SK_Man_Full_01.SK_Man_Full_01'"));
	/*if (MeshMujerAux.Succeeded())
	{
		MeshMujer = MeshMujerAux.Object;
	}*/
	if (MeshHombreAux.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("Cargamos la malla del hombre"));
		MeshHombre = MeshHombreAux.Object;
	}
	if (MeshMujerAux.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("Cargamos la malla de la mujer"));
		MeshMujer = MeshMujerAux.Object;
	}

	UCapsuleComponent* CapsuleComponentAux;
	CapsuleComponentAux = GetCapsuleComponent();
	CapsuleComponentAux->SetGenerateOverlapEvents(true);
	CapsuleComponentAux->OnComponentBeginOverlap.AddDynamic(this, &AMyProject1Character::OnOverlapBegin);

	monedas = TArray<AMoneda*>();

	CoinCount = 0;

	Player = nullptr;
	CoinHUD = nullptr;
}


void AMyProject1Character::BeginPlay()
{
	Super::BeginPlay();
	//Player = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	//CoinHUD = Cast<ACoinHUD>(Player->GetHUD());
	Player = GetWorld()->GetFirstPlayerController();
	if (Player)
	{
		CoinHUD = Cast<ACoinHUD>(Player->GetHUD());
	}
}
//////////////////////////////////////////////////////////////////////////
// Input

void AMyProject1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyProject1Character::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyProject1Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMyProject1Character::TouchStopped);
	PlayerInputComponent->BindAction("CambiarPersona", IE_Pressed, this, &AMyProject1Character::doSomething);
}

void AMyProject1Character::doSomething()
{
	UE_LOG(LogTemp, Warning, TEXT("Llamamos a la funcion doSomething"));
	//cambiar disfraz al personaje 
	GetMesh()->SetSkeletalMesh(MeshMujer);

	if (isMale)
	{
		GetMesh()->SetSkeletalMesh(MeshMujer);
		isMale = false;
	}
	else
	{
		GetMesh()->SetSkeletalMesh(MeshHombre);
		isMale = true;
	}
}

void AMyProject1Character::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AMyProject1Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AMyProject1Character::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AMyProject1Character::AumentarVidas()
{
	numeroVidas++;
	UE_LOG(LogTemp, Warning, TEXT("Numero de vidas: %d"), numeroVidas);
}

void AMyProject1Character::DisminuirVidas()
{
	numeroVidas--;
	UE_LOG(LogTemp, Warning, TEXT("Numero de vidas: %d"), numeroVidas);
}

void AMyProject1Character::AumentarTamanio() {
	FVector NewScale = GetActorScale3D();
	NewScale += FVector(0.05f, 0.05f, 0.05f);
	if (NewScale.X >= 2.0f) {
		NewScale = FVector(2.0f, 2.0f, 2.0f);
		SetActorScale3D(NewScale);
	}
	else
	{
		SetActorScale3D(NewScale);
	}
	UE_LOG(LogTemp, Warning, TEXT("Vector: X=%f, Y=%f, Z=%f"), NewScale.X, NewScale.Y, NewScale.Z);
}


void AMyProject1Character::DisminuirTamanio() {
	FVector NewScale = GetActorScale3D();
	NewScale -= FVector(0.05f, 0.05f, 0.05f);
	if (NewScale.X<=0.5f) {
		NewScale = FVector(0.5f, 0.5f, 0.5f);
		SetActorScale3D(NewScale);
	}
	else
	{
		SetActorScale3D(NewScale);
	}
	UE_LOG(LogTemp, Warning, TEXT("Vector: X=%f, Y=%f, Z=%f"), NewScale.X, NewScale.Y, NewScale.Z);
}

void AMyProject1Character::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		// Handle collision logic here
		UE_LOG(LogTemp, Warning, TEXT("Collision detected with %s"), *OtherActor->GetName());

		AMoneda* MonedaActor = Cast<AMoneda>(OtherActor);
		if (MonedaActor)
		{
			// Successfully cast to Moneda, you can now use MonedaActor
			MonedaActor->Ocultar(); // Replace with your actual function
			//puntaje += monedaActor->puntaje

			//monedas.Add(MonedaActor);
			if (!monedas.Contains(MonedaActor)) {
				monedas.Add(MonedaActor);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Monedas Recogidas %d"), monedas.Num()));
				CoinCount++;
				CoinHUD->UpdateCoinWidget(CoinCount);
			}
		}

	}
}


