// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkerBase.h"

#include "Components/SphereComponent.h"

// Sets default values
AMarkerBase::AMarkerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// ...

	MarkerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnRoot"));
	RootComponent = MarkerRoot;

#if WITH_EDITOR
	MarkerVis = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnVis"));
	MarkerVis->SetupAttachment(RootComponent);
	MarkerVis->SetSphereRadius(100.f);
#endif
}

// Called when the game starts or when spawned
void AMarkerBase::BeginPlay()
{
	Super::BeginPlay();
	
	// ...


}
