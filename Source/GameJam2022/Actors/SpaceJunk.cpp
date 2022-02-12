// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceJunk.h"

#include "GameJam2022/Characters/PlayerBlackholeCharacter.h"

#include "GameJam2022/Components/AmbientMotionComponent.h"

#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"

#include "Materials/MaterialInstanceDynamic.h"

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

	AmbientMotion = CreateDefaultSubobject<UAmbientMotionComponent>(TEXT("Ambient Motion"));
}

// Called when the game starts or when spawned
void ASpaceJunk::BeginPlay()
{
	Super::BeginPlay();
	
	// ...

	if (MeshPivot && AmbientMotion)
	{
		AmbientMotion->SetMeshPivot(MeshPivot);
	}

	UMaterialInstanceDynamic* MeshMaterial = Mesh->CreateDynamicMaterialInstance(0);
	if (MeshMaterial)
	{
		DynamicMaterial = MeshMaterial;
		Mesh->SetMaterial(0, DynamicMaterial);
	}

	Mesh->SetRelativeScale3D(FVector::OneVector * ObjectScale);
}

// Called every frame
void ASpaceJunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...

	UpdatePosition();

	if (DynamicMaterial)
	{
		if (APlayerBlackholeCharacter* PC = Cast<APlayerBlackholeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			if (ObjectScale > PC->GetObjectScale())
			{
				DynamicMaterial->SetVectorParameterValue("FlashColor", FVector(1.0f, 0.f, 0.f));
			}
			else
			{
				DynamicMaterial->SetVectorParameterValue("FlashColor", FVector(0.f, 1.f, 0.f));
			}
		}
	}
}

void ASpaceJunk::UpdatePosition()
{
	if (APlayerBlackholeCharacter* PC = Cast<APlayerBlackholeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		float PlayerDistance = FMath::Abs(FVector::Dist(PC->GetActorLocation(), GetActorLocation()));
		FVector PlayerDirection = FVector(PC->GetActorLocation() - GetActorLocation()).GetClampedToSize(100.f, 100.f);

		if (PlayerDistance > GravityRange) { return; }

		// ...

		FVector CurrentLocation = GetActorLocation();

		float GravityRatio = 1 - (PlayerDistance / GravityRange);

		if (PlayerDistance < GravityRange / 4)
		{
			GravityRatio += 16 * (1 - (PlayerDistance / (GravityRange / 4)));
		}
		else if (PlayerDistance < GravityRange / 2)
		{
			GravityRatio += 4 * (1 - (PlayerDistance / (GravityRange / 2)));
		}

		if (GEngine)
		{
			FString DebugMessage = TEXT("Gravity Ratio = ");
			DebugMessage.Append(FString::SanitizeFloat(GravityRatio));
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Cyan, DebugMessage);
		}

		FVector TargetLocation = GetActorLocation() + (PlayerDirection);

		float GravityScaleFactor = ObjectScale - PC->GetObjectScale() + 1.f;

		FVector LerpLocation = FMath::Lerp(CurrentLocation, TargetLocation, (GravtyStrength / GravityScaleFactor) * GravityRatio * GetWorld()->GetDeltaSeconds());

		SetActorLocation(FVector(LerpLocation.X, LerpLocation.Y, 0.f));
	}
}

