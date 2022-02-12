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

	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity", meta = (AllowPrivateAccess = "True"))
		float GravityRange = 1500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity", meta = (AllowPrivateAccess = "True"))
		float GravtyStrength = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity", meta = (AllowPrivateAccess = "True"))
		int ObjectScale = 1;

	void UpdatePosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ASpaceJunk();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
