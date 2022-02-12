// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceJunk.h"

#include "GameJam2022/Characters/PlayerBlackholeCharacter.h"

#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"

#include "Kismet/GameplayStatics.h"

#include "GameFramework/Character.h"

// Sets default values
ASpaceJunk::ASpaceJunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ...

	RootPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootPivot;

	CollectionTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collection Trigger"));
	CollectionTrigger->SetupAttachment(RootComponent);
	CollectionTrigger->InitCapsuleSize(200.f, 200.f);
	CollectionTrigger->SetCollisionProfileName(TEXT("Trigger"));

	MeshPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Mesh Pivot"));
	MeshPivot->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(MeshPivot);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ASpaceJunk::BeginPlay()
{
	Super::BeginPlay();
	
	// ...


}

// Called every frame
void ASpaceJunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...

	UpdatePosition();
}

void ASpaceJunk::UpdatePosition()
{
	if (APlayerBlackholeCharacter* PC = Cast<APlayerBlackholeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		float PlayerDistance = FMath::Abs(FVector::Dist(PC->GetActorLocation(), GetActorLocation()));

		if (PlayerDistance > GravityRange) { return; }

		// ...

		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation = PC->GetActorLocation();

		float GravityRatio = 1 - (PlayerDistance / GravityRange);

		if (PlayerDistance < GravityRange / 4)
		{
			GravityRatio += (PlayerDistance / (GravityRange / 4));
		}

		FVector LerpLocation = FMath::Lerp(CurrentLocation, TargetLocation, GravtyStrength * GravityRatio * GetWorld()->GetDeltaSeconds());

		SetActorLocation(FVector(LerpLocation.X, LerpLocation.Y, 0.f));
	}
}

