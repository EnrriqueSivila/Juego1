// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "COmponents/StaticMeshComponent.h"
#include "Moneda.h"
#include "CoinClass.h"
#include "GameFramework/PlayerController.h"
#include "CoinHUD.h"
#include "MyProject1Character.generated.h"

UCLASS(config=Game)
class AMyProject1Character : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	virtual void BeginPlay() override;
	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
	void doSomething();

public:
	AMyProject1Character();

	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//DECLARAR DOS VARIABLES DE TIPO MESH
	USkeletalMesh* MeshHombre;
	USkeletalMesh* MeshMujer;
	bool isMale;
	//agregar una variable numero de vidas
	int numeroVidas;
	void AumentarVidas();
	void AumentarTamanio();
	void DisminuirTamanio();
	void DisminuirVidas();

	APlayerController* Player;
	ACoinHUD* CoinHUD;

	int CoinCount;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monedas")
	TArray<AMoneda*> monedas;
};
