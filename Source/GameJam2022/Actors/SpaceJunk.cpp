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
	CollectionTrigger->InitCapsuleSize(50.f, 50.f);
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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> R2Asset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_R2D2.SM_R2D2'"));
	if (R2Asset.Succeeded())
	{
		Scale01.Add(R2Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ToiletAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_toilet.SM_toilet'"));
	if (ToiletAsset.Succeeded())
	{
		Scale01.Add(ToiletAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>  SputnikAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Sputnik.SM_Sputnik'"));
	if (SputnikAsset.Succeeded())
	{
		Scale01.Add(SputnikAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>  DogAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Dog.SM_Dog'"));
	if (DogAsset.Succeeded())
	{
		Scale01.Add(DogAsset.Object);
	}

	//Scale 02

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TardisAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Tardis.SM_Tardis'"));
	if (TardisAsset.Succeeded())
	{
		Scale02.Add(TardisAsset.Object);
	}

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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> UFOAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_ufo.SM_ufo'"));
	if (UFOAsset.Succeeded())
	{
		Scale02.Add(UFOAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TeslaAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/tesla_roadster_low.tesla_roadster_low'"));
	if (TeslaAsset.Succeeded())
	{
		Scale02.Add(TeslaAsset.Object);
	}

	//Scale03

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Satellite03Asset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_sattelite3.SM_sattelite3'"));
	if (Satellite03Asset.Succeeded())
	{
		Scale03.Add(Satellite03Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asteroid01Asset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/asteroid_1_low.asteroid_1_low'"));
	if (Asteroid01Asset.Succeeded())
	{
		Scale03.Add(Asteroid01Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asteroid02Asset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/asteroid_2_low.asteroid_2_low'"));
	if (Asteroid02Asset.Succeeded())
	{
		Scale03.Add(Asteroid02Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asteroid03Asset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/crystal_asteroid_low.crystal_asteroid_low'"));
	if (Asteroid03Asset.Succeeded())
	{
		Scale03.Add(Asteroid03Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShuttleAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Space_Shuttle.SM_Space_Shuttle'"));
	if (ShuttleAsset.Succeeded())
	{
		Scale03.Add(ShuttleAsset.Object);
	}

	//Scale04

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Satellite04Asset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_sattelite4.SM_sattelite4'"));
	if (Satellite04Asset.Succeeded())
	{
		Scale04.Add(Satellite04Asset.Object);
	}

	//Scale05

	if (Asteroid01Asset.Succeeded())
	{
		Scale05.Add(Asteroid01Asset.Object);
	}

	if (Asteroid02Asset.Succeeded())
	{
		Scale05.Add(Asteroid02Asset.Object);
	}

	if (Asteroid03Asset.Succeeded())
	{
		Scale05.Add(Asteroid03Asset.Object);
	}

	//scale06
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StarDestroyerAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Star_Destroyer.SM_Star_Destroyer'"));
	if (StarDestroyerAsset.Succeeded())
	{
		Scale06.Add(StarDestroyerAsset.Object);
	}

	//Scale07

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DeathStarAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Death_Star.SM_Death_Star'"));
	if (DeathStarAsset.Succeeded())
	{
		Scale07.Add(DeathStarAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MercuryAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Planets_Mercury.SM_Planets_Mercury'"));
	if (MercuryAsset.Succeeded())
	{
		Scale07.Add(MercuryAsset.Object);
	}

	//Scale08
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MarsAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Planets_Mars.SM_Planets_Mars'"));
	if (MarsAsset.Succeeded())
	{
		Scale08.Add(MercuryAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> VenusAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Planets_Venus.SM_Planets_Venus'"));
	if (VenusAsset.Succeeded())
	{
		Scale08.Add(VenusAsset.Object);
	}

	//Scale09
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NeptuneAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Planets_Neptune.SM_Planets_Neptune'"));
	if (NeptuneAsset.Succeeded())
	{
		Scale09.Add(NeptuneAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> UranusAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Planets_Uranus.SM_Planets_Uranus'"));
	if (UranusAsset.Succeeded())
	{
		Scale09.Add(UranusAsset.Object);
	}

	//Scale10
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SaturnAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Planets_Saturn.SM_Planets_Saturn'"));
	if (SaturnAsset.Succeeded())
	{
		Scale10.Add(UranusAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> JupiterAsset(TEXT("StaticMesh'/Game/GameJam2022/Meshes/Suckable/SM_Planets_Jupiter.SM_Planets_Jupiter'"));
	if (JupiterAsset.Succeeded())
	{
		Scale10.Add(JupiterAsset.Object);
	}
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

	// ...

	if (MeshPivot && AmbientMotion)
	{
		AmbientMotion->SetMeshPivot(MeshPivot);
	}

	// ...

	if (ASpawnManager* SM = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass())))
	{
		SM->GetNewTravelDirection(this);
	}
}

void ASpaceJunk::SetupObjectScale()
{
	if (APlayerBlackholeCharacter* PC = Cast<APlayerBlackholeCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerBlackholeCharacter::StaticClass())))
	{
		ObjectScale = FMath::RandRange(FMath::Clamp(INT(PC->GetObjectScale()) - 4, 1, 10), INT(PC->GetObjectScale()) + 3);

		// ...

		UStaticMesh* TempMesh;
		UMaterialInstance* TempMaterial;

		switch (INT(ObjectScale))
		{
		case 1:
			TempMesh = Scale01[FMath::RandRange(0, Scale01.Num() - 1)];
			TempMaterial = Cast<UMaterialInstance>(TempMesh->GetMaterial(0)->GetMaterial());
			Mesh->SetStaticMesh(TempMesh);
			Mesh->SetMaterial(0, TempMaterial);

			break;
		case 2:
			TempMesh = Scale02[FMath::RandRange(0, Scale02.Num() - 1)];
			TempMaterial = Cast<UMaterialInstance>(TempMesh->GetMaterial(0)->GetMaterial());
			Mesh->SetStaticMesh(TempMesh);
			Mesh->SetMaterial(0, TempMaterial);

			break;
		case 3:
			TempMesh = Scale03[FMath::RandRange(0, Scale03.Num() - 1)];
			TempMaterial = Cast<UMaterialInstance>(TempMesh->GetMaterial(0)->GetMaterial());
			Mesh->SetStaticMesh(TempMesh);
			Mesh->SetMaterial(0, TempMaterial);

			break;
		case 4:
			TempMesh = Scale04[FMath::RandRange(0, Scale04.Num() - 1)];
			TempMaterial = Cast<UMaterialInstance>(TempMesh->GetMaterial(0)->GetMaterial());
			Mesh->SetStaticMesh(TempMesh);
			Mesh->SetMaterial(0, TempMaterial);

			break;
		case 5:
			TempMesh = Scale05[FMath::RandRange(0, Scale05.Num() - 1)];
			TempMaterial = Cast<UMaterialInstance>(TempMesh->GetMaterial(0)->GetMaterial());
			Mesh->SetStaticMesh(TempMesh);
			Mesh->SetMaterial(0, TempMaterial);

			break;
		case 6:
			TempMesh = Scale06[FMath::RandRange(0, Scale06.Num() - 1)];
			TempMaterial = Cast<UMaterialInstance>(TempMesh->GetMaterial(0)->GetMaterial());
			Mesh->SetStaticMesh(TempMesh);
			Mesh->SetMaterial(0, TempMaterial);

			break;
		case 7:
			TempMesh = Scale07[FMath::RandRange(0, Scale07.Num() - 1)];
			TempMaterial = Cast<UMaterialInstance>(TempMesh->GetMaterial(0)->GetMaterial());
			Mesh->SetStaticMesh(TempMesh);
			Mesh->SetMaterial(0, TempMaterial);

			break;
		case 8:
			TempMesh = Scale08[FMath::RandRange(0, Scale08.Num() - 1)];
			TempMaterial = Cast<UMaterialInstance>(TempMesh->GetMaterial(0)->GetMaterial());
			Mesh->SetStaticMesh(TempMesh);
			Mesh->SetMaterial(0, TempMaterial);

			break;
		case 9:
			TempMesh = Scale09[FMath::RandRange(0, Scale09.Num() - 1)];
			TempMaterial = Cast<UMaterialInstance>(TempMesh->GetMaterial(0)->GetMaterial());
			Mesh->SetStaticMesh(TempMesh);
			Mesh->SetMaterial(0, TempMaterial);

			break;
		case 10:
			TempMesh = Scale10[FMath::RandRange(0, Scale10.Num() - 1)];
			TempMaterial = Cast<UMaterialInstance>(TempMesh->GetMaterial(0)->GetMaterial());
			Mesh->SetStaticMesh(TempMesh);
			Mesh->SetMaterial(0, TempMaterial);

			break;
		default:

			break;
		}

		// ...


		// ...

		UMaterialInstanceDynamic* MeshMaterial = Mesh->CreateDynamicMaterialInstance(0);
		if (MeshMaterial)
		{
			DynamicMaterial = MeshMaterial;
			Mesh->SetMaterial(0, DynamicMaterial);
		}

		// ...

		SetActorScale3D((FVector::OneVector * ObjectScale * .6f) - (FVector::OneVector * ((PC->GetObjectScale() - 1.5f) * 0.2f)));

	}
}

// Called every frame
void ASpaceJunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...

	UpdatePosition();

	// ...
}

void ASpaceJunk::UpdatePosition()
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = CurrentLocation += ((TravelDirection / ObjectScale)* 4.f * GetWorld()->DeltaTimeSeconds);

	DistanceTravelled += ((100.f / ObjectScale) * 4.f * GetWorld()->DeltaTimeSeconds);
	if (DistanceTravelled > 6500.f)
	{
		if (ASpawnManager* SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass())))
		{
			SpawnManager->HandleRespawn(this);

			SetupObjectScale();

			if (AmbientMotion)
			{
				AmbientMotion->ResetRotation();
			}
		}

		DistanceTravelled = 0.f;

		// ...

		return;
	}

	SetActorLocation(TargetLocation);

	if (APlayerBlackholeCharacter* PC = Cast<APlayerBlackholeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (DynamicMaterial)
		{
			if ((float)ObjectScale < PC->GetObjectScale())
			{
				DynamicMaterial->SetVectorParameterValue("FlashColor", FVector(0.f, 1.f, 0.f));
				bIsTooBig = false;
			}
			else
			{
				DynamicMaterial->SetVectorParameterValue("FlashColor", FVector(1.f, 0.f, 0.f));
				bIsTooBig = true;
			}
		}

		float PlayerDistance = FMath::Abs(FVector::Dist(PC->GetActorLocation(), GetActorLocation()));
		FVector PlayerDirection = FVector(PC->GetActorLocation() - GetActorLocation()).GetClampedToSize(100.f, 100.f);

		if (PlayerDistance > GravityRange) { return; }

		// ...

		CurrentLocation = GetActorLocation();

		float GravityRatio = 1 - (PlayerDistance / GravityRange);

		if (PlayerDistance < GravityRange / 4)
		{
			GravityRatio += 16 * (1 - (PlayerDistance / (GravityRange / 4)));
		}
		else if (PlayerDistance < GravityRange / 2)
		{
			GravityRatio += 4 * (1 - (PlayerDistance / (GravityRange / 2)));
		}

		if ((PlayerDistance < GravityRange / 6) && (ObjectScale <= PC->GetObjectScale()))
		{
			FVector CurrentScale = GetActorScale3D();
			FVector TargetScale = FVector::OneVector * 0.5f;

			SetActorScale3D(FMath::Lerp(CurrentScale, TargetScale, 4.f * GetWorld()->DeltaTimeSeconds));
		}
		else
		{
			SetActorScale3D((FVector::OneVector * ObjectScale * .6f) - (FVector::OneVector * ((PC->GetObjectScale() - 1.5f) * 0.2f)));
		}

#if WITH_EDITOR
		if (GEngine)
		{
			FString DebugMessage = TEXT("Gravity Ratio = ");
			DebugMessage.Append(FString::SanitizeFloat(GravityRatio));
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Cyan, DebugMessage);
		}
#endif

		TargetLocation = (GetActorLocation() + (PlayerDirection));

		float GravityScaleFactor = FMath::Clamp((ObjectScale - PC->GetObjectScale()), 0.f, 10.f) + 1.f;

		FVector LerpLocation = FMath::Lerp(CurrentLocation, TargetLocation, (GravtyStrength / GravityScaleFactor) * GravityRatio * GetWorld()->GetDeltaSeconds());

		SetActorLocation(FVector(LerpLocation.X, LerpLocation.Y, 0.f));
	}
}

void ASpaceJunk::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActive) { return; }

	// ...

	if (!OtherActor) { return; }

	if (!OtherComp) { return; }

	// ...

	if (APlayerBlackholeCharacter* PC = Cast<APlayerBlackholeCharacter>(OtherActor))
	{
		if (Cast<UCapsuleComponent>(OtherComp))
		{
			if (bIsTooBig) { 
				bIsActive = false; 
				
				PC->OnDeath(); 

				return; 
			}

			PC->HandleCollection(this);

			if (ASpawnManager* SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass())))
			{
				SpawnManager->HandleRespawn(this);

				SetupObjectScale();

				if (AmbientMotion)
				{
					AmbientMotion->ResetRotation();
				}
			}

			DistanceTravelled = 0.f;

			bIsActive = true;
		}
	}
}

void ASpaceJunk::SetTravelPath(FVector WaypointDirection)
{
	TravelDirection = FVector(FVector(WaypointDirection - GetActorLocation()) * FVector(1.f, 1.f, 0.f)).GetClampedToSize(100.f, 100.f);

#if WITH_EDITOR
	if (GEngine)
	{
		FString DebugMessage = TEXT("New Travel Direction = ");
		DebugMessage.AppendInt(INT(TravelDirection.X));
		DebugMessage.Append(TEXT(", "));
		DebugMessage.AppendInt(INT(TravelDirection.Y));
		DebugMessage.Append(TEXT(", "));
		DebugMessage.AppendInt(INT(TravelDirection.Z));
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, DebugMessage);
	}
#endif
}