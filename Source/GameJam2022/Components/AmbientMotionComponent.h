// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmbientMotionComponent.generated.h"

USTRUCT(BlueprintType)
struct FRotationAxis {

	GENERATED_BODY()

	bool RotateOnX = true;

	bool RotateOnY = true;

	bool RotateOnZ = true;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAM2022_API UAmbientMotionComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	USceneComponent* MeshPivot;

	float MaxRotationRate = 15.f;
	float RotationRate;

	FRotationAxis RotationalAxis;

	void UpdateRotation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UAmbientMotionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void SetMeshPivot(USceneComponent* NewPivot) { MeshPivot = NewPivot; ResetRotation();  }

	UFUNCTION(BLueprintCallable)
		void ResetRotation();
		
};
