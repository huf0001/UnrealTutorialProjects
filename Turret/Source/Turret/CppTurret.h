// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "CppTurret.generated.h"

UCLASS()
class TURRET_API ACppTurret : public AActor
{
	GENERATED_BODY()

private:

#pragma region Private Serialized Variables
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly)
		USkeletalMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Beam;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Target1;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Target2;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* BeamTarget;

	UPROPERTY()
		FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere)
		float ChangeTargetDelay = 5.0f;

	UPROPERTY(EditAnywhere)
		float RotationRateMultiplier = 1.0f;

	UPROPERTY(EditAnywhere)
		float TargetRotationErrorMargin = 1.0f;

#pragma endregion

#pragma region Private Non-Serialized Variables

	int TimerCount = 0;
	FRotator LookAtRotation;
	FRotator TargetRotation;
	FRotator RotationDelta;

#pragma endregion

#pragma region Setup Methods

public:	
	// Sets default values for this actor's properties
	ACppTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Recurring Methods

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void UpdateLookAtTarget(float DeltaTime);

		FRotator MinMagnitude(FRotator a, FRotator b);

	UFUNCTION()
		void ChangeBeamTarget();

#pragma endregion

};
