// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBoxPlataformas.generated.h"

/**
 *
 */
UCLASS()
class MYPROJECT1_API ATriggerBoxPlataformas : public ATriggerBox
{
	GENERATED_BODY()

protected:
	ATriggerBoxPlataformas();
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PLATAFORMA")
	TArray<AStaticMeshActor*> plataforma;
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
	void MoverPlataforma(float distance);
};