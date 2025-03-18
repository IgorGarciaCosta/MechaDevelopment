// Fill out your copyright notice in the Description page of Project Settings.

#include "MechaCharacter.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMechaCharacter::AMechaCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMechaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMechaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsHatchOpen)
	{
		DrawLaserLineTracers();
	}
}

// Called to bind functionality to input
void AMechaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMechaCharacter::DrawLaserLineTracers()
{
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	if (!SkeletalMesh)
	{
		return;
	}

	FVector LSocketLocation = SkeletalMesh->GetSocketLocation("Turret-LSocket");
	FVector RSocketLocation = SkeletalMesh->GetSocketLocation("Turret-RSocket");

	FVector ForwardVector = GetActorForwardVector();

	FVector LEndLocation = LSocketLocation + (ForwardVector * 500.0f);
	FVector REndLocation = RSocketLocation + (ForwardVector * 500.0f);

	// Line trace for the left socket
	FHitResult LHitResult;
	GetWorld()->LineTraceSingleByChannel(
		LHitResult,
		LSocketLocation,
		LEndLocation,
		ECC_Visibility // Change to the appropriate collision channel if needed
	);

	// Line trace for the right socket
	FHitResult RHitResult;
	GetWorld()->LineTraceSingleByChannel(
		RHitResult,
		RSocketLocation,
		REndLocation,
		ECC_Visibility // Change to the appropriate collision channel if needed
	);

	// Draw debug lines
	DrawDebugLine(GetWorld(), LSocketLocation, LEndLocation, FColor::Red, false, -1, 0, 1);
	DrawDebugLine(GetWorld(), RSocketLocation, REndLocation, FColor::Red, false, -1, 0, 1);
}
