#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include <Components/BoxComponent.h>
#include "Moneda.generated.h"

UCLASS()
class MYPROJECT1_API AMoneda : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoneda();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Ocultar();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CoinMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;

	UMaterial* MaterialMoneda;
};
