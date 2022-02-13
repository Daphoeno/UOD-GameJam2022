// Fill out your copyright notice in the Description page of Project Settings.


#include "AmbientMotionComponent.h"

// Sets default values for this component's properties
UAmbientMotionComponent::UAmbientMotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAmbientMotionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	RotationRate = FMath::RandRange(MaxRotationRate * 0.1f, MaxRotationRate);

	// ...
}

void UAmbientMotionComponent::ResetRotation()
{
	if (!MeshPivot) { return; }

	FRotator CurrentRotation = MeshPivot->GetRelativeRotation();
	FRotator NewRotation = CurrentRotation;

	if (RotationalAxis.RotateOnX)
	{
		NewRotation += FRotator(0.f, 0.f, FMath::RandRange(-90.f, 90.f));
	}

	if (RotationalAxis.RotateOnY)
	{
		NewRotation += FRotator(FMath::RandRange(-90.f, 90.f), 0.f, 0.f);
	}

	if (RotationalAxis.RotateOnZ)
	{
		NewRotation += FRotator(0.f, FMath::RandRange(-90.f, 90.f), 0.f);
	}

	MeshPivot->SetRelativeRotation(NewRotation);
}

// Called every frame
void UAmbientMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (MeshPivot)
	{
		UpdateRotation();
	}
}

void UAmbientMotionComponent::UpdateRotation()
{
	if (!MeshPivot) { return; }

	FRotator CurrentRotation = MeshPivot->GetRelativeRotation();
	FRotator NewRotation = CurrentRotation;

	if (RotationalAxis.RotateOnX)
	{
		NewRotation += FRotator(0.f, 0.f, RotationRate * GetWorld()->DeltaTimeSeconds);
	}

	if (RotationalAxis.RotateOnY)
	{
		NewRotation += FRotator(RotationRate * GetWorld()->DeltaTimeSeconds, 0.f, 0.f);
	}

	if (RotationalAxis.RotateOnZ)
	{
		NewRotation += FRotator(0.f, RotationRate * GetWorld()->DeltaTimeSeconds, 0.f);
	}

	MeshPivot->SetRelativeRotation(NewRotation);
}

