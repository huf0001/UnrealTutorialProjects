// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppTurret.generated.h"

UCLASS()
class TURRET_API ACppTurret : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly)
		USkeletalMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Beam;

public:	
	// Sets default values for this actor's properties
	ACppTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
