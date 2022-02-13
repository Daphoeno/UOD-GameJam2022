// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBlackholeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class GAMEJAM2022_API APlayerBlackholeCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
		UStaticMeshComponent* BlackholeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
		UCameraComponent* Camera;

	float CameraFollowAmount = 0.3f;
	float CameraFollowSpeed = 4.f;

	float ObjectScale = 1.8f;

	void UpdateCameraPosition();

	float DefaultScale;
	void IncreaseScale(int NewObjectScale);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Sets default values for this character's properties
	APlayerBlackholeCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void OnDeath();

	void MoveForward(float value);
	void MoveRight(float value);

	float GetObjectScale() const { return ObjectScale; }

	UFUNCTION(BlueprintCallable)
		void HandleCollection(ASpaceJunk* CollectedActor);

};
