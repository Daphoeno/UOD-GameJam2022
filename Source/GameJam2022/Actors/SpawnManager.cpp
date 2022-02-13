// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

#include "GameJam2022/Actors/Markers/SpawnMarker.h"
#include "GameJam2022/Actors/Markers/TravelMarker.h"
#include "GameJam2022/Actors/SpaceJunk.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// ...

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	// ...

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnMarker::StaticClass(), SpawnMarkers);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATravelMarker::StaticClass(), TravelMarkers);
}

bool ASpawnManager::HandleRespawn(ASpaceJunk* RespawnActor)
{
	if (!RespawnActor) { return false; }

	// ...

	if (SpawnMarkers.Num() <= 0) { return false; }

	AActor* SelectedSpawnMarker = SpawnMarkers[FMath::RandRange(0, SpawnMarkers.Num() - 1)];

	if (!SelectedSpawnMarker) { return false; }

	RespawnActor->SetActorLocation(SelectedSpawnMarker->GetActorLocation(), false);

	// ...

	if (TravelMarkers.Num() <= 0) { return false; }

	AActor* SelectedTravelMarker = TravelMarkers[FMath::RandRange(0, TravelMarkers.Num() - 1)];

	if (!SelectedTravelMarker) { return false; }

	RespawnActor->SetTravelPath(SelectedTravelMarker->GetActorLocation());

	// ...

	return true;
}

void ASpawnManager::GetNewTravelDirection(ASpaceJunk* Actor)
{
	if (!Actor) { return; }

	// ...

	if (TravelMarkers.Num() <= 0) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATravelMarker::StaticClass(), TravelMarkers);
	}

	AActor* SelectedTravelMarker = TravelMarkers[FMath::RandRange(0, TravelMarkers.Num() - 1)];

	if (!SelectedTravelMarker) { return; }

	Actor->SetTravelPath(SelectedTravelMarker->GetActorLocation());
}
