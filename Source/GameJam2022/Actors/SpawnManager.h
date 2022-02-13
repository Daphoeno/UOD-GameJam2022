// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

class ASpawnPoint;
class ATravelWaypoint;

UCLASS()
class GAMEJAM2022_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
private:

	TArray<AActor*> SpawnMarkers;

	TArray<AActor*> TravelMarkers;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ASpawnManager();

	UFUNCTION(BlueprintCallable)
		bool HandleRespawn(ASpaceJunk* RespawnActor);

};
