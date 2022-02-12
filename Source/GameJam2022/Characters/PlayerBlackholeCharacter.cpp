// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBlackholeCharacter.h"

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
	SpringArm->TargetArmLength = 2000.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	
}

// Called when the game starts or when spawned
void APlayerBlackholeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// ...


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
