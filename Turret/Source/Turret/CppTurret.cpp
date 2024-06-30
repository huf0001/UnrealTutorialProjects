// Fill out your copyright notice in the Description page of Project Settings.


#include "CppTurret.h"
#include "Kismet/KismetMathLibrary.h"
#include "TurretAnimInterface.h"

#pragma region Setup Methods

// Sets default values
ACppTurret::ACppTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(Root);

	Beam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beam"));
	Beam->SetupAttachment(TurretMesh, TEXT("BeamSocket"));

	Target1 = CreateDefaultSubobject<USceneComponent>(TEXT("Target1"));
	Target1->SetupAttachment(Root);

	Target2 = CreateDefaultSubobject<USceneComponent>(TEXT("Target2"));
	Target2->SetupAttachment(Root);

	BeamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("BeamTarget"));
	BeamTarget->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ACppTurret::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACppTurret::ChangeBeamTarget, ChangeTargetDelay, true, 1);
}

#pragma endregion

#pragma region Recurring Methods

// Called every frame
void ACppTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLookAtTarget(DeltaTime);
}

void ACppTurret::UpdateLookAtTarget(float DeltaTime)
{
	if (LookAtRotation.Equals(TargetRotation, TargetRotationErrorMargin))
	{
		return;
	}

	//From tutorial
	/*
	LookAtRotation += RotationDelta * RotationRateMultiplier * DeltaTime;
	*/

	//Custom code that clamps the rotation
	FRotator RotationChange = RotationDelta * RotationRateMultiplier * DeltaTime;
	FRotator RotationRemaining = TargetRotation - LookAtRotation;
	LookAtRotation += MinMagnitude(RotationChange, RotationRemaining);
	
	//Continue from tutorial
	if (TurretMesh->GetAnimInstance()->Implements<UTurretAnimInterface>())
	{
		ITurretAnimInterface::Execute_UpdateLookAtRotation(TurretMesh->GetAnimInstance(), LookAtRotation);
	}
}

/// <summary>
/// Return the FRotator with the smaller magnitude. Assumes a and b are rotations from the same starting rotation
/// to the same end rotation, and that the rotation components (Pitch, Roll, Yaw) are facing the same direction 
/// (+ or -) for a and b, but the magnitude of one is greater than the other.
/// </summary>
/// <param name="a">FRotator a.</param>
/// <param name="b">FRotator b.</param>
/// <returns>Whichever of a or b has the smaller magnitude.</returns>
FRotator ACppTurret::MinMagnitude(FRotator a, FRotator b)
{
	//fabs() gets the absolute value of a float. Can use abs() to do that for floats and ints, but fabs() is
	//apparently more efficient for floats.
	if (
		fabs(a.Pitch) <= fabs(b.Pitch) &&
		fabs(a.Roll) <= fabs(b.Roll) &&
		fabs(a.Yaw) <= fabs(b.Yaw)
		)
	{
		return a;
	}

	return b;
}

void ACppTurret::ChangeBeamTarget()
{
	TimerCount++;

	if (TimerCount % 2 == 0)
	{
		BeamTarget->SetWorldLocation(Target1->GetComponentLocation());
	}
	else
	{
		BeamTarget->SetWorldLocation(Target2->GetComponentLocation());
	}

	FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
	FVector End = BeamTarget->GetComponentLocation();
	TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

	RotationDelta = TargetRotation - LookAtRotation;
	RotationDelta.Normalize();
}

#pragma endregion
