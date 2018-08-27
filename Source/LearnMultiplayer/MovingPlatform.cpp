// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
	Speed = 30.0f;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	InitialTargetLocation = GetTransform().TransformPosition(TargetLocation);
	InitialStartLocation = GetActorLocation();
	
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0 && HasAuthority() )
	{
		FVector Location = GetActorLocation();

		if (FVector::Distance(InitialStartLocation, Location) > FVector::Distance(InitialStartLocation, InitialTargetLocation))
		{
			FVector temp = InitialTargetLocation;
			InitialTargetLocation = InitialStartLocation;
			InitialStartLocation = temp;
		}

		FVector Direction = (InitialTargetLocation - InitialStartLocation).GetSafeNormal();
		Location += Speed * DeltaTime * Direction;
		SetActorLocation(Location);
	}
}


void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}
