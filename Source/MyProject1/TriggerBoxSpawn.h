#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBoxSpawn.generated.h"

UCLASS()
class MYPROJECT1_API ATriggerBoxSpawn : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:

	ATriggerBoxSpawn();
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	bool isFirstTime = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tipo")
	int tipo;
};

