// Fill out your copyright notice in the Description page of Project Settings.

#include "MechaCharacter.h"
#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

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

	LaserStartLocationLeft = SkeletalMesh->GetSocketLocation("Turret-LSocket");
	LaserStartLocationRight = SkeletalMesh->GetSocketLocation("Turret-RSocket");

	FVector ForwardVector = GetActorForwardVector();

	FVector LEndLocation = LaserStartLocationLeft + (ForwardVector * 500.0f);
	FVector REndLocation = LaserStartLocationRight + (ForwardVector * 500.0f);

	// Line trace for the left socket
	GetWorld()->LineTraceSingleByChannel(
		LaserHitResultLeft,
		LaserStartLocationLeft,
		LEndLocation,
		ECC_Visibility // Change to the appropriate collision channel if needed
	);

	// Line trace for the right socket
	GetWorld()->LineTraceSingleByChannel(
		LaserHitResultRight,
		LaserStartLocationRight,
		REndLocation,
		ECC_Visibility // Change to the appropriate collision channel if needed
	);

	// Draw debug lines
	DrawDebugLine(GetWorld(), LaserStartLocationLeft, LEndLocation, FColor::Red, false, -1, 0, 1);
	DrawDebugLine(GetWorld(), LaserStartLocationRight, REndLocation, FColor::Red, false, -1, 0, 1);
}

void AMechaCharacter::ShootLaser()
{
	if (bIsHatchOpen)
	{
		// Play launch effects
		if (LaunchLaserEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), LaunchLaserEffect, LaserStartLocationLeft);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), LaunchLaserEffect, LaserStartLocationRight);
		}

		// Play laser sounds at the start locations
		if (LaserSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaserSound, LaserStartLocationLeft);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaserSound, LaserStartLocationRight);
		}

		// Play hit effects
		if (LaserHitResultLeft.bBlockingHit)
		{
			if (HitLaserEffect)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitLaserEffect, LaserHitResultLeft.Location);
			}
			if (HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, LaserHitResultLeft.Location);
			}
		}

		if (LaserHitResultRight.bBlockingHit)
		{
			if (HitLaserEffect)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitLaserEffect, LaserHitResultRight.Location);
			}
			if (HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, LaserHitResultRight.Location);
			}
		}
	}
}
