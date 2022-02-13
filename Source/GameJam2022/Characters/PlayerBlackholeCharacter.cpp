// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBlackholeCharacter.h"

#include "GameJam2022/Actors/SpaceJunk.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Camera/CameraComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerBlackholeCharacter::APlayerBlackholeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ...

	BlackholeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackholeMesh"));
	BlackholeMesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-75.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 5000.f;
	SpringArm->bEnableCameraLag = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetFieldOfView(35.f);

	
}

// Called when the game starts or when spawned
void APlayerBlackholeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// ...

	DefaultScale = BlackholeMesh->GetRelativeScale3D().Size();

	BlackholeMesh->SetRelativeScale3D((FVector::OneVector * DefaultScale) + (FVector::OneVector * ((ObjectScale - 1.5f) * 0.05f)));
}

void APlayerBlackholeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ...

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveForward", this, &APlayerBlackholeCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerBlackholeCharacter::MoveRight);

}

void APlayerBlackholeCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void APlayerBlackholeCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

// Called every frame
void APlayerBlackholeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...

	UpdateCameraPosition();
}

void APlayerBlackholeCharacter::UpdateCameraPosition()
{
	FVector CurrentPosition = SpringArm->GetComponentLocation();
	FVector TargetPosition = CurrentPosition;

	TargetPosition = FVector(GetActorLocation() * CameraFollowAmount);

	// Lerp springarm
	SpringArm->SetWorldLocation(FMath::Lerp(CurrentPosition, TargetPosition, CameraFollowSpeed * GetWorld()->GetDeltaSeconds()));
}

void APlayerBlackholeCharacter::IncreaseScale(int NewObjectScale)
{
	ObjectScale += (.08f);

#if WITH_EDITOR
	if (GEngine)
	{
		FString DebugMessage = TEXT("New Player Size = ");
		DebugMessage.Append(FString::SanitizeFloat(ObjectScale));
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, DebugMessage);
	}
#endif

	BlackholeMesh->SetRelativeScale3D((FVector::OneVector * DefaultScale) + (FVector::OneVector * ((ObjectScale - 1.5f) * 0.15f)));
}

void APlayerBlackholeCharacter::HandleCollection(ASpaceJunk* CollectedActor)
{
	if (!CollectedActor) { return; }

	// ...

	IncreaseScale(CollectedActor->GetObjectScale());
}