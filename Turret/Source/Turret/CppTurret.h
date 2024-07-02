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

#pragma region Protected Serialized Variables

protected:
	//Beam length variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float BeamLength = 1000.0f;

#pragma endregion

#pragma region Private Serialized Variables

private:
	//Turret Components
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly)
		USkeletalMeshComponent* TurretMesh;

	//Beam and Targeting Components
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Beam;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Target1;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Target2;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* BeamTarget;

	//Turret Shooting Components
	UPROPERTY(EditDefaultsOnly, Category = Shooting)
		UParticleSystemComponent* P_MuzzleFlash;

	UPROPERTY(EditDefaultsOnly, Category = Shooting)
		USoundBase* ShootSound;

	UPROPERTY()
		FTimerHandle ShootTimerHandle;
		

	//Rotation variables
	UPROPERTY()
		FTimerHandle ChangeTargetTimerHandle;

	UPROPERTY(EditAnywhere)
		float ChangeTargetDelay = 5.0f;

	UPROPERTY(EditAnywhere)
		float RotationRateMultiplier = 1.0f;

	UPROPERTY(EditAnywhere)
		float TargetRotationErrorMargin = 1.0f;

	//Beam Length variables

	UPROPERTY()
		FTimerHandle TraceTimerHandle;

	//Enemy Detection variables
	UPROPERTY()
		AActor* Enemy;

	UPROPERTY(EditAnywhere)
		float FollowEnemyRotationRateMultiplier = 1.0f;

	//Shooting variables
	UPROPERTY(EditAnywhere)
		float ShootingDelay = 0.4f;

#pragma endregion

#pragma region Protected Non-Serialized Variables

protected:

	//Beam Length variables
	FCollisionQueryParams CollQueryParams;

#pragma endregion

#pragma region Private Non-Serialized Variables

private:

	//Rotation variables
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

	UFUNCTION(BlueprintCallable)
		void SetBeamLength(float Length);

	UFUNCTION()
		void TraceBeam();

	UFUNCTION()
		void CheckEnemy(AActor* HitActor);

	UFUNCTION()
		void FollowEnemy(float DeltaTime);

	UFUNCTION()
		void Shoot();

#pragma endregion

};
