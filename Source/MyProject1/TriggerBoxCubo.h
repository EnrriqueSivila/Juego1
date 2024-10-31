// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBoxCubo.generated.h"       

/**
 * 
 */
UCLASS()
class MYPROJECT1_API ATriggerBoxCubo : public ATriggerBox
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tipo")
    int tipo;
    ATriggerBoxCubo();

    UFUNCTION()
    void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};

