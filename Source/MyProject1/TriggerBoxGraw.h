// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBoxGraw.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT1_API ATriggerBoxGraw : public ATriggerBox
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tipo")
	int tipo;
	ATriggerBoxGraw();
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	int contador = 0;
};
