// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceJunk.h"

#include "GameJam2022/Actors/SpawnManager.h"

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
	CollectionTrigger->InitCapsuleSize(100.f, 100.f);
	CollectionTrigger->SetCollisionProfileName(TEXT("Trigger"));

	MeshPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Mesh Pivot"));
	MeshPivot->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(MeshPivot);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AmbientMotion = CreateDefaultSubobject<UAmbientMotionComponent>(TEXT("Ambient Motion"));

	// ...

	//Scale 01

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AmongusAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Amongus.SM_Amongus'"));
	if (AmongusAsset.Succeeded())
	{
		Scale01.Add(AmongusAsset.Object);
	}

	//Scale 02

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Satellite01Asset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_sattelite1.SM_sattelite1'"));
	if (Satellite01Asset.Succeeded())
	{
		Scale02.Add(Satellite01Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Satellite02Asset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_sattelite2.SM_sattelite2'"));
	if (Satellite02Asset.Succeeded())
	{
		Scale02.Add(Satellite02Asset.Object);
	}

	//Scale03

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Satellite03Asset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_sattelite3.SM_sattelite3'"));
	if (Satellite03Asset.Succeeded())
	{
		Scale03.Add(Satellite03Asset.Object);
	}

	//Scale04

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Satellite04Asset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_sattelite4.SM_sattelite4'"));
	if (Satellite04Asset.Succeeded())
	{
		Scale04.Add(Satellite04Asset.Object);
	}

	//Scale05
}

// Called when the game starts or when spawned
void ASpaceJunk::BeginPlay()
{
	Super::BeginPlay();
	
	// ...

	// Collection overlap
	CollectionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASpaceJunk::OnOverlapBegin);

	// ...

	SetupObjectScale();

	UMaterialInstanceDynamic* MeshMaterial = Mesh->CreateDynamicMaterialInstance(0);
	if (MeshMaterial)
	{
		DynamicMaterial = MeshMaterial;
		Mesh->SetMaterial(0, DynamicMaterial);
	}

	// ...

	if (MeshPivot && AmbientMotion)
	{
		AmbientMotion->SetMeshPivot(MeshPivot);
	}

}

void ASpaceJunk::SetupObjectScale()
{
	ObjectScale = FMath::RandRange(1,4);

	// ...

	switch (INT(ObjectScale))
	{
	case 1:
		Mesh->SetStaticMesh(Scale01[FMath::RandRange(0, Scale01.Num() - 1)]);

		break;
	case 2:
		Mesh->SetStaticMesh(Scale02[FMath::RandRange(0, Scale02.Num() - 1)]);

		break;
	case 3:
		Mesh->SetStaticMesh(Scale03[FMath::RandRange(0, Scale03.Num() - 1)]);

		break;
	case 4:
		Mesh->SetStaticMesh(Scale04[FMath::RandRange(0, Scale04.Num() - 1)]);

		break;
	default:

		break;
	}

	// ...

	SetActorScale3D(FVector::OneVector * ObjectScale * .75f);
}

// Called every frame
void ASpaceJunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...

	UpdatePosition();

	// ...

	if (APlayerBlackholeCharacter* PC = Cast<APlayerBlackholeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		SetActorScale3D((FVector::OneVector * ObjectScale * .75f) / FMath::Clamp(PC->GetObjectScale() - 1, 1.f, 100.f));

		// ...

		if (DynamicMaterial)
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
			GravityRatio += 32 * (1 - (PlayerDistance / (GravityRange / 4)));
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

		float GravityScaleFactor = (ObjectScale - PC->GetObjectScale()) + 1.f;

		FVector LerpLocation = FMath::Lerp(CurrentLocation, TargetLocation, (GravtyStrength / GravityScaleFactor) * GravityRatio * GetWorld()->GetDeltaSeconds());

		SetActorLocation(FVector(LerpLocation.X, LerpLocation.Y, 0.f));
	}
}

void ASpaceJunk::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) { return; }

	if (!OtherComp) { return; }

	// ...

	if (APlayerBlackholeCharacter* PC = Cast<APlayerBlackholeCharacter>(OtherActor))
	{
		if (PC->GetObjectScale() < ObjectScale) { return; }

		if (Cast<UCapsuleComponent>(OtherComp))
		{
			PC->HandleCollection(this);

			if (ASpawnManager* SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass())))
			{
				SpawnManager->HandleRespawn(this);
			}
		}
	}
}

void ASpaceJunk::SetTravelPath(FVector WaypointDirection)
{

}