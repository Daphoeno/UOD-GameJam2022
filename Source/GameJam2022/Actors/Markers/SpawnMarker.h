// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MarkerBase.h"
#include "SpawnMarker.generated.h"

UCLASS()
class GAMEJAM2022_API ASpawnMarker : public AMarkerBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ASpawnMarker();

};
