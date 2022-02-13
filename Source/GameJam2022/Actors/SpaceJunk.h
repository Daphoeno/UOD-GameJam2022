// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceJunk.generated.h"

class UCapsuleComponent;
class UMaterialInstanceDynamic;

class UAmbientMotionComponent;

UCLASS()
class GAMEJAM2022_API ASpaceJunk : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
		USceneComponent* RootPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
		USceneComponent* MeshPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
		UCapsuleComponent* CollectionTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
		UAmbientMotionComponent* AmbientMotion;

	// ...

	// Mesh loading

	TArray<UStaticMesh*> Scale01;
	TArray<UStaticMesh*> Scale02;
	TArray<UStaticMesh*> Scale03;
	TArray<UStaticMesh*> Scale04;
	TArray<UStaticMesh*> Scale05;
	TArray<UStaticMesh*> Scale06;
	TArray<UStaticMesh*> Scale07;
	TArray<UStaticMesh*> Scale08;
	TArray<UStaticMesh*> Scale09;
	TArray<UStaticMesh*> Scale10;


	void SetupObjectScale();

	// ...

	bool bIsTooBig = false;

	bool bIsActive = true;

	// ...

	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity", meta = (AllowPrivateAccess = "True"))
		float GravityRange = 1500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity", meta = (AllowPrivateAccess = "True"))
		float GravtyStrength = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity", meta = (AllowPrivateAccess = "True"))
		int ObjectScale = 1;

	float DistanceTravelled = 0.f;

	void UpdatePosition();

	FVector TravelDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Sets default values for this actor's properties
	ASpaceJunk();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetObjectScale(int NewObjectScale) { ObjectScale = NewObjectScale; }

	UFUNCTION(BlueprintCallable)
		void SetTravelPath(FVector WaypointDirection);

	UFUNCTION(BlueprintCallable)
		int GetObjectScale() const { return ObjectScale; }
};
