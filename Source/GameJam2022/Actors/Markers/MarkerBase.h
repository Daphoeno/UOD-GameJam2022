// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MarkerBase.generated.h"

class USphereComponent;

UCLASS()
class GAMEJAM2022_API AMarkerBase : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
		USceneComponent* MarkerRoot;

#if WITH_EDITOR
	USphereComponent* MarkerVis;
#endif

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USceneComponent* GetMarkerRoot() const { return MarkerRoot; }

#if WITH_EDITOR
	USphereComponent* GetMarkerVis() const { return MarkerVis; }
#endif

public:
	// Sets default values for this actor's properties
	AMarkerBase();

};
