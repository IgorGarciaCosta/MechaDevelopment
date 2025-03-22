// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NiagaraSystem.h"
#include "Sound/SoundBase.h"
#include "MechaCharacter.generated.h"

UCLASS()
class ROBOTCHARACTER_API AMechaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMechaCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHatchOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* LaunchLaserEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* HitLaserEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* LaserSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* HitSound;

	UFUNCTION(BlueprintCallable)
	void ShootLaser();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ApplyImpact(FHitResult LeftImpart, FHitResult RightImpact);

private:
	// Function to draw laser line tracers
	void DrawLaserLineTracers();

	FHitResult LaserHitResultLeft;
	FHitResult LaserHitResultRight;
	FVector LaserStartLocationLeft;
	FVector LaserStartLocationRight;
};

